/* ---------------------------------------------------------------------------- *\
 *  Film Aficionado is public domain software. Promotional material images,
 *  if present, are copyrighted by the respective copyright owners and should
 *  only be used under the provisions dictated by those copyright holders.
 *  There are no warranties expressed on implied.
\* ---------------------------------------------------------------------------- */

#ifndef PHP_WIN32
    #include <unistd.h>				// Needed for sleep()
	#define Sleep(s)	sleep(s)
#endif

#include "dvdaf.h"
#include "field.h"
#include "dstring.h"

/* ----------------------------------------------------------------------------------------- *\
 * IPC variables
 * ----------------------------------------------------------------------------------------- */
static t_shm				gs_ipc_mem;
static const int			gp_magic[]				 = {0xddaf, 0xdafd, 0xafdd, 0xfdda, 0xeeb0, 0xeb0e, 0xb0ee, 0x0eeb}; // magic numbers
static const int			gn_magic_count			 = sizeof(gp_magic) / sizeof(int);
static const int			gn_magic_print_1		 = ('d')|('v'<<8)|('d'<<16)|('a'<<24);
static const int			gn_magic_print_2		 = ('f')|('m'<<8)|('e'<<16)|('m'<<24);

/* ----------------------------------------------------------------------------------------- *\
 * mutex_lock(int* pn_mutex, int n_resource_id)
 *
 * Waits until resource is avaliable, locks it and then returns
 * ----------------------------------------------------------------------------------------- */
void mutex_lock_(int *pn_mutex, int n_resource_id)
{
	if ( n_resource_id < 0 || n_resource_id > 31 ) return;
	while ( test_and_set(n_resource_id, pn_mutex) ) Sleep(1);
}
void mutex_lock2_(int *pn_mutex_1, int n_resource_id_1, int *pn_mutex_2, int n_resource_id_2)
{
	if ( n_resource_id_1 < 0 || n_resource_id_1 > 31 ) return;
	if ( n_resource_id_2 < 0 || n_resource_id_2 > 31 ) return;
	for (  ;  ;  )
	{
		while (   test_and_set(n_resource_id_1, pn_mutex_1) ) Sleep(1);
		if    ( ! test_and_set(n_resource_id_2, pn_mutex_2) ) return;
		test_and_clear(n_resource_id_1, pn_mutex_1);
		Sleep(1);
	}
}

/* ----------------------------------------------------------------------------------------- *\
 * mutex_unlock(int* pn_mutex, int n_resource_id)
 *
 * Unlocks a resource
 * ----------------------------------------------------------------------------------------- */
void mutex_unlock_(int *pn_mutex, int n_resource_id)
{
	if ( n_resource_id < 0 || n_resource_id > 31 ) return;
	test_and_clear(n_resource_id, pn_mutex);
}
void mutex_unlock2_(int *pn_mutex_1, int n_resource_id_1, int *pn_mutex_2, int n_resource_id_2)
{
	if ( n_resource_id_1 < 0 || n_resource_id_1 > 31 ) return;
	if ( n_resource_id_2 < 0 || n_resource_id_2 > 31 ) return;
	test_and_clear(n_resource_id_1, pn_mutex_1);
	test_and_clear(n_resource_id_2, pn_mutex_2);
}

/* ----------------------------------------------------------------------------------------- *\
 * ipc_open(t_shm *p_ipc_mem, int n_size, const int *p_magic, const int n_magic_count)
 *
 * Finds or allocates a shared memory area identified by magic numbers.
 *
 *	  Usage:
 *	  Get shared memory
 *		ipc_open(&gs_ipc_mem, sizeof(t_field_hash) * gp_field_count, gp_magic, gn_magic_count);
 *		mutex_lock2(&(gs_ipc_mem.n_mutex), 0, &(gs_ipc_mem.p_block->n_mutex), 0);
 *			field_hash_calc((t_field_hash*)&(gs_ipc_mem.p_block->c_data_start));
 *		mutex_unlock2(&(gs_ipc_mem.n_mutex), 0, &(gs_ipc_mem.p_block->n_mutex), 0);
 *
 *	  Release shared memory
 *		ipc_free(&gs_ipc_mem);
 *
 * ----------------------------------------------------------------------------------------- */
void ipc_open(t_shm *p_ipc_mem, int n_size, const int *p_magic, const int n_magic_count)
{
	struct shmid_ds shm;
	int i;

	n_size += sizeof(t_shm_block) - sizeof(unsigned char*);	// account for our control structures, just in case things grow,
															// but we will reflect the allocated size in "p_ipc_mem->n_size"
	mutex_lock(&(p_ipc_mem->n_mutex), 0)
		// try to find an existing shared memory area for this process
		for ( i = 0 ; p_ipc_mem->n_shmid <= 0 && i < n_magic_count ; i++ )
		{
			p_ipc_mem->s_key	= p_magic[i];
			p_ipc_mem->n_size	= 0;
			p_ipc_mem->pt_block	= (void*)-1;
			p_ipc_mem->n_shmid	= shmget(p_ipc_mem->s_key, 0, 0666 | IPC_CREAT | IPC_EXCL);
			if ( p_ipc_mem->n_shmid > 0 )
			{
				if ( shmctl(p_ipc_mem->n_shmid, IPC_STAT, &shm) == 0 )
					p_ipc_mem->n_size = shm.shm_segsz;
				if ( p_ipc_mem->n_size > 0 )
					p_ipc_mem->pt_block = shmat(p_ipc_mem->n_shmid, NULL, 0);
				if ( p_ipc_mem->pt_block != (void*)-1 )
				{
					if ( p_ipc_mem->pt_block->n_magic_print_1 != gn_magic_print_1 || p_ipc_mem->pt_block->n_magic_print_2 != gn_magic_print_2 )
					{
						shmdt(p_ipc_mem->pt_block);		// oops, magic numbers do not match -- not ours -- detach!
						p_ipc_mem->pt_block = (void*)-1;
					}
				}
				if ( p_ipc_mem->pt_block == (void*)-1 )
					p_ipc_mem->n_shmid = -1;
			}
		}

		// was not able to find it, create a new one
		for ( i = 0 ; p_ipc_mem->n_shmid <= 0 && i < n_magic_count ; i++ )
		{
			p_ipc_mem->s_key	= p_magic[i];
			p_ipc_mem->n_size	= 0;
			p_ipc_mem->pt_block	= (void*)-1;
			p_ipc_mem->n_shmid	= shmget(p_ipc_mem->s_key, n_size, 0666 | IPC_CREAT);
			if ( p_ipc_mem->n_shmid > 0 )
			{
				if ( shmctl(p_ipc_mem->n_shmid, IPC_STAT, &shm) == 0 )
					p_ipc_mem->n_size = shm.shm_segsz;
				if ( p_ipc_mem->n_size > 0 )
					p_ipc_mem->pt_block = shmat(p_ipc_mem->n_shmid, NULL, 0);
				if ( p_ipc_mem->pt_block != (void*)-1 )
				{
					memset( p_ipc_mem->pt_block, 0, p_ipc_mem->n_size);
					p_ipc_mem->pt_block->n_magic_print_1 = gn_magic_print_1;	// brand it with our magic number - part 1
					p_ipc_mem->pt_block->n_magic_print_2 = gn_magic_print_2;	// brand it with our magic number - part 2
					p_ipc_mem->pt_block->n_mutex		 = 0;					// done by memset, but we will make it clear...  :)
				}
				else
				{
					p_ipc_mem->n_shmid = -1;
				}
			}
		}
		if ( (i = p_ipc_mem->n_shmid) > 0 )
		{
			p_ipc_mem->n_references++;
		}
	#ifdef PHP_WIN32
	#pragma warning(disable:4127)	// Ignore leve4 warning C4127: conditional expression is constant
	#endif
	mutex_unlock(&(p_ipc_mem->n_mutex), 0);
	#ifdef PHP_WIN32
	#pragma warning(4:4127)			// Re-enable leve4 warning C4127
	#endif

	if ( i <= 0 ) ZEND_PUTS ("DVDAF: Could not allocate/attach the shared memory segment.");
}

/* ----------------------------------------------------------------------------------------- *\
 * void ipc_free(t_shm *p_ipc_mem)
 * 
 * Decrements reference, and possibly detaches and/or mark shared memory segment for destruction
 * ----------------------------------------------------------------------------------------- */
void ipc_free(t_shm *p_ipc_mem)
{
	struct shmid_ds shm;
	int n_attachments = 0;

	mutex_lock(&(p_ipc_mem->n_mutex), 0);
		if ( p_ipc_mem->n_shmid > 0 )
		{
			if ( --p_ipc_mem->n_references <= 0 )
			{
				// See how many attachements are left
				if ( shmctl(p_ipc_mem->n_shmid, IPC_STAT, &shm) == 0 )
					n_attachments = shm.shm_nattch;
				// Last attachement delete!
				if ( n_attachments <= 1 )
					shmctl(p_ipc_mem->n_shmid, IPC_RMID, NULL);
				// Last reference... detach!
				shmdt(p_ipc_mem->pt_block);
				// Clean up structures
				p_ipc_mem->n_references	= 0;
				p_ipc_mem->s_key		= 0;
				p_ipc_mem->n_shmid		= 0;
				p_ipc_mem->n_size		= 0;
				p_ipc_mem->pt_block		= NULL;
			}
		}
	#ifdef PHP_WIN32
	#pragma warning(disable:4127)	// Ignore leve4 warning C4127: conditional expression is constant
	#endif
	mutex_unlock(&(p_ipc_mem->n_mutex), 0);
	#ifdef PHP_WIN32
	#pragma warning(4:4127)			// Re-enable leve4 warning C4127
	#endif
}

/* ========================================================================================= */
