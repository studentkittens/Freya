# 1 "Request.cc"
# 1 "<eingebaut>"
# 1 "<Kommandozeile>"
# 1 "Request.cc"
# 1 "Request.hh" 1




# 1 "/usr/local/include/glyr/glyr.h" 1 3
# 35 "/usr/local/include/glyr/glyr.h" 3
# 1 "/usr/local/include/glyr/types.h" 1 3
# 35 "/usr/local/include/glyr/types.h" 3
# 1 "/usr/include/stdlib.h" 1 3 4
# 25 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 358 "/usr/include/features.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 378 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 379 "/usr/include/sys/cdefs.h" 2 3 4
# 359 "/usr/include/features.h" 2 3 4
# 382 "/usr/include/features.h" 3 4
# 1 "/usr/include/gnu/stubs.h" 1 3 4



# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 5 "/usr/include/gnu/stubs.h" 2 3 4




# 1 "/usr/include/gnu/stubs-64.h" 1 3 4
# 10 "/usr/include/gnu/stubs.h" 2 3 4
# 383 "/usr/include/features.h" 2 3 4
# 26 "/usr/include/stdlib.h" 2 3 4







# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.6.3/include/stddef.h" 1 3 4
# 212 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.6.3/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 34 "/usr/include/stdlib.h" 2 3 4

extern "C" {






# 1 "/usr/include/bits/waitflags.h" 1 3 4
# 43 "/usr/include/stdlib.h" 2 3 4
# 1 "/usr/include/bits/waitstatus.h" 1 3 4
# 65 "/usr/include/bits/waitstatus.h" 3 4
# 1 "/usr/include/endian.h" 1 3 4
# 37 "/usr/include/endian.h" 3 4
# 1 "/usr/include/bits/endian.h" 1 3 4
# 38 "/usr/include/endian.h" 2 3 4
# 61 "/usr/include/endian.h" 3 4
# 1 "/usr/include/bits/byteswap.h" 1 3 4
# 28 "/usr/include/bits/byteswap.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 29 "/usr/include/bits/byteswap.h" 2 3 4
# 62 "/usr/include/endian.h" 2 3 4
# 66 "/usr/include/bits/waitstatus.h" 2 3 4

union wait
  {
    int w_status;
    struct
      {

 unsigned int __w_termsig:7;
 unsigned int __w_coredump:1;
 unsigned int __w_retcode:8;
 unsigned int:16;







      } __wait_terminated;
    struct
      {

 unsigned int __w_stopval:8;
 unsigned int __w_stopsig:8;
 unsigned int:16;






      } __wait_stopped;
  };
# 44 "/usr/include/stdlib.h" 2 3 4
# 96 "/usr/include/stdlib.h" 3 4


typedef struct
  {
    int quot;
    int rem;
  } div_t;



typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;







__extension__ typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;


# 140 "/usr/include/stdlib.h" 3 4
extern size_t __ctype_get_mb_cur_max (void) throw () ;




extern double atof (__const char *__nptr)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern int atoi (__const char *__nptr)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern long int atol (__const char *__nptr)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;





__extension__ extern long long int atoll (__const char *__nptr)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;





extern double strtod (__const char *__restrict __nptr,
        char **__restrict __endptr)
     throw () __attribute__ ((__nonnull__ (1))) ;





extern float strtof (__const char *__restrict __nptr,
       char **__restrict __endptr) throw () __attribute__ ((__nonnull__ (1))) ;

extern long double strtold (__const char *__restrict __nptr,
       char **__restrict __endptr)
     throw () __attribute__ ((__nonnull__ (1))) ;





extern long int strtol (__const char *__restrict __nptr,
   char **__restrict __endptr, int __base)
     throw () __attribute__ ((__nonnull__ (1))) ;

extern unsigned long int strtoul (__const char *__restrict __nptr,
      char **__restrict __endptr, int __base)
     throw () __attribute__ ((__nonnull__ (1))) ;




__extension__
extern long long int strtoq (__const char *__restrict __nptr,
        char **__restrict __endptr, int __base)
     throw () __attribute__ ((__nonnull__ (1))) ;

__extension__
extern unsigned long long int strtouq (__const char *__restrict __nptr,
           char **__restrict __endptr, int __base)
     throw () __attribute__ ((__nonnull__ (1))) ;





__extension__
extern long long int strtoll (__const char *__restrict __nptr,
         char **__restrict __endptr, int __base)
     throw () __attribute__ ((__nonnull__ (1))) ;

__extension__
extern unsigned long long int strtoull (__const char *__restrict __nptr,
     char **__restrict __endptr, int __base)
     throw () __attribute__ ((__nonnull__ (1))) ;

# 236 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/xlocale.h" 1 3 4
# 28 "/usr/include/xlocale.h" 3 4
typedef struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
} *__locale_t;


typedef __locale_t locale_t;
# 237 "/usr/include/stdlib.h" 2 3 4



extern long int strtol_l (__const char *__restrict __nptr,
     char **__restrict __endptr, int __base,
     __locale_t __loc) throw () __attribute__ ((__nonnull__ (1, 4))) ;

extern unsigned long int strtoul_l (__const char *__restrict __nptr,
        char **__restrict __endptr,
        int __base, __locale_t __loc)
     throw () __attribute__ ((__nonnull__ (1, 4))) ;

__extension__
extern long long int strtoll_l (__const char *__restrict __nptr,
    char **__restrict __endptr, int __base,
    __locale_t __loc)
     throw () __attribute__ ((__nonnull__ (1, 4))) ;

__extension__
extern unsigned long long int strtoull_l (__const char *__restrict __nptr,
       char **__restrict __endptr,
       int __base, __locale_t __loc)
     throw () __attribute__ ((__nonnull__ (1, 4))) ;

extern double strtod_l (__const char *__restrict __nptr,
   char **__restrict __endptr, __locale_t __loc)
     throw () __attribute__ ((__nonnull__ (1, 3))) ;

extern float strtof_l (__const char *__restrict __nptr,
         char **__restrict __endptr, __locale_t __loc)
     throw () __attribute__ ((__nonnull__ (1, 3))) ;

extern long double strtold_l (__const char *__restrict __nptr,
         char **__restrict __endptr,
         __locale_t __loc)
     throw () __attribute__ ((__nonnull__ (1, 3))) ;
# 311 "/usr/include/stdlib.h" 3 4
extern char *l64a (long int __n) throw () ;


extern long int a64l (__const char *__s)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;




# 1 "/usr/include/sys/types.h" 1 3 4
# 28 "/usr/include/sys/types.h" 3 4
extern "C" {

# 1 "/usr/include/bits/types.h" 1 3 4
# 28 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 29 "/usr/include/bits/types.h" 2 3 4


typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;







typedef long int __quad_t;
typedef unsigned long int __u_quad_t;
# 131 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/typesizes.h" 1 3 4
# 132 "/usr/include/bits/types.h" 2 3 4


typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;

typedef int __daddr_t;
typedef long int __swblk_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;

typedef long int __ssize_t;



typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;
# 31 "/usr/include/sys/types.h" 2 3 4



typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;




typedef __loff_t loff_t;



typedef __ino_t ino_t;






typedef __ino64_t ino64_t;




typedef __dev_t dev_t;




typedef __gid_t gid_t;




typedef __mode_t mode_t;




typedef __nlink_t nlink_t;




typedef __uid_t uid_t;





typedef __off_t off_t;






typedef __off64_t off64_t;




typedef __pid_t pid_t;





typedef __id_t id_t;




typedef __ssize_t ssize_t;





typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;





typedef __key_t key_t;
# 133 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/time.h" 1 3 4
# 58 "/usr/include/time.h" 3 4


typedef __clock_t clock_t;



# 74 "/usr/include/time.h" 3 4


typedef __time_t time_t;



# 92 "/usr/include/time.h" 3 4
typedef __clockid_t clockid_t;
# 104 "/usr/include/time.h" 3 4
typedef __timer_t timer_t;
# 134 "/usr/include/sys/types.h" 2 3 4



typedef __useconds_t useconds_t;



typedef __suseconds_t suseconds_t;





# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.6.3/include/stddef.h" 1 3 4
# 148 "/usr/include/sys/types.h" 2 3 4



typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
# 195 "/usr/include/sys/types.h" 3 4
typedef int int8_t __attribute__ ((__mode__ (__QI__)));
typedef int int16_t __attribute__ ((__mode__ (__HI__)));
typedef int int32_t __attribute__ ((__mode__ (__SI__)));
typedef int int64_t __attribute__ ((__mode__ (__DI__)));


typedef unsigned int u_int8_t __attribute__ ((__mode__ (__QI__)));
typedef unsigned int u_int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int u_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int u_int64_t __attribute__ ((__mode__ (__DI__)));

typedef int register_t __attribute__ ((__mode__ (__word__)));
# 220 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/sys/select.h" 1 3 4
# 31 "/usr/include/sys/select.h" 3 4
# 1 "/usr/include/bits/select.h" 1 3 4
# 23 "/usr/include/bits/select.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 24 "/usr/include/bits/select.h" 2 3 4
# 32 "/usr/include/sys/select.h" 2 3 4


# 1 "/usr/include/bits/sigset.h" 1 3 4
# 24 "/usr/include/bits/sigset.h" 3 4
typedef int __sig_atomic_t;




typedef struct
  {
    unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
  } __sigset_t;
# 35 "/usr/include/sys/select.h" 2 3 4



typedef __sigset_t sigset_t;





# 1 "/usr/include/time.h" 1 3 4
# 120 "/usr/include/time.h" 3 4
struct timespec
  {
    __time_t tv_sec;
    long int tv_nsec;
  };
# 45 "/usr/include/sys/select.h" 2 3 4

# 1 "/usr/include/bits/time.h" 1 3 4
# 31 "/usr/include/bits/time.h" 3 4
struct timeval
  {
    __time_t tv_sec;
    __suseconds_t tv_usec;
  };
# 47 "/usr/include/sys/select.h" 2 3 4
# 55 "/usr/include/sys/select.h" 3 4
typedef long int __fd_mask;
# 65 "/usr/include/sys/select.h" 3 4
typedef struct
  {



    __fd_mask fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];





  } fd_set;






typedef __fd_mask fd_mask;
# 97 "/usr/include/sys/select.h" 3 4
extern "C" {
# 107 "/usr/include/sys/select.h" 3 4
extern int select (int __nfds, fd_set *__restrict __readfds,
     fd_set *__restrict __writefds,
     fd_set *__restrict __exceptfds,
     struct timeval *__restrict __timeout);
# 119 "/usr/include/sys/select.h" 3 4
extern int pselect (int __nfds, fd_set *__restrict __readfds,
      fd_set *__restrict __writefds,
      fd_set *__restrict __exceptfds,
      const struct timespec *__restrict __timeout,
      const __sigset_t *__restrict __sigmask);
# 132 "/usr/include/sys/select.h" 3 4
}
# 221 "/usr/include/sys/types.h" 2 3 4


# 1 "/usr/include/sys/sysmacros.h" 1 3 4
# 30 "/usr/include/sys/sysmacros.h" 3 4
extern "C" {

__extension__
extern unsigned int gnu_dev_major (unsigned long long int __dev)
     throw () __attribute__ ((__const__));
__extension__
extern unsigned int gnu_dev_minor (unsigned long long int __dev)
     throw () __attribute__ ((__const__));
__extension__
extern unsigned long long int gnu_dev_makedev (unsigned int __major,
            unsigned int __minor)
     throw () __attribute__ ((__const__));
# 64 "/usr/include/sys/sysmacros.h" 3 4
}
# 224 "/usr/include/sys/types.h" 2 3 4





typedef __blksize_t blksize_t;






typedef __blkcnt_t blkcnt_t;



typedef __fsblkcnt_t fsblkcnt_t;



typedef __fsfilcnt_t fsfilcnt_t;
# 263 "/usr/include/sys/types.h" 3 4
typedef __blkcnt64_t blkcnt64_t;
typedef __fsblkcnt64_t fsblkcnt64_t;
typedef __fsfilcnt64_t fsfilcnt64_t;





# 1 "/usr/include/bits/pthreadtypes.h" 1 3 4
# 23 "/usr/include/bits/pthreadtypes.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 24 "/usr/include/bits/pthreadtypes.h" 2 3 4
# 50 "/usr/include/bits/pthreadtypes.h" 3 4
typedef unsigned long int pthread_t;


typedef union
{
  char __size[56];
  long int __align;
} pthread_attr_t;



typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;
# 76 "/usr/include/bits/pthreadtypes.h" 3 4
typedef union
{
  struct __pthread_mutex_s
  {
    int __lock;
    unsigned int __count;
    int __owner;

    unsigned int __nusers;



    int __kind;

    int __spins;
    __pthread_list_t __list;
# 101 "/usr/include/bits/pthreadtypes.h" 3 4
  } __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_mutexattr_t;




typedef union
{
  struct
  {
    int __lock;
    unsigned int __futex;
    __extension__ unsigned long long int __total_seq;
    __extension__ unsigned long long int __wakeup_seq;
    __extension__ unsigned long long int __woken_seq;
    void *__mutex;
    unsigned int __nwaiters;
    unsigned int __broadcast_seq;
  } __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_condattr_t;



typedef unsigned int pthread_key_t;



typedef int pthread_once_t;





typedef union
{

  struct
  {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;
    int __writer;
    int __shared;
    unsigned long int __pad1;
    unsigned long int __pad2;


    unsigned int __flags;
  } __data;
# 187 "/usr/include/bits/pthreadtypes.h" 3 4
  char __size[56];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;





typedef volatile int pthread_spinlock_t;




typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;
# 272 "/usr/include/sys/types.h" 2 3 4


}
# 321 "/usr/include/stdlib.h" 2 3 4






extern long int random (void) throw ();


extern void srandom (unsigned int __seed) throw ();





extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) throw () __attribute__ ((__nonnull__ (2)));



extern char *setstate (char *__statebuf) throw () __attribute__ ((__nonnull__ (1)));







struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };

extern int random_r (struct random_data *__restrict __buf,
       int32_t *__restrict __result) throw () __attribute__ ((__nonnull__ (1, 2)));

extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     throw () __attribute__ ((__nonnull__ (2)));

extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
   size_t __statelen,
   struct random_data *__restrict __buf)
     throw () __attribute__ ((__nonnull__ (2, 4)));

extern int setstate_r (char *__restrict __statebuf,
         struct random_data *__restrict __buf)
     throw () __attribute__ ((__nonnull__ (1, 2)));






extern int rand (void) throw ();

extern void srand (unsigned int __seed) throw ();




extern int rand_r (unsigned int *__seed) throw ();







extern double drand48 (void) throw ();
extern double erand48 (unsigned short int __xsubi[3]) throw () __attribute__ ((__nonnull__ (1)));


extern long int lrand48 (void) throw ();
extern long int nrand48 (unsigned short int __xsubi[3])
     throw () __attribute__ ((__nonnull__ (1)));


extern long int mrand48 (void) throw ();
extern long int jrand48 (unsigned short int __xsubi[3])
     throw () __attribute__ ((__nonnull__ (1)));


extern void srand48 (long int __seedval) throw ();
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     throw () __attribute__ ((__nonnull__ (1)));
extern void lcong48 (unsigned short int __param[7]) throw () __attribute__ ((__nonnull__ (1)));





struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    unsigned long long int __a;
  };


extern int drand48_r (struct drand48_data *__restrict __buffer,
        double *__restrict __result) throw () __attribute__ ((__nonnull__ (1, 2)));
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        double *__restrict __result) throw () __attribute__ ((__nonnull__ (1, 2)));


extern int lrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int mrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     throw () __attribute__ ((__nonnull__ (2)));

extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer) throw () __attribute__ ((__nonnull__ (1, 2)));

extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer)
     throw () __attribute__ ((__nonnull__ (1, 2)));









extern void *malloc (size_t __size) throw () __attribute__ ((__malloc__)) ;

extern void *calloc (size_t __nmemb, size_t __size)
     throw () __attribute__ ((__malloc__)) ;










extern void *realloc (void *__ptr, size_t __size)
     throw () __attribute__ ((__warn_unused_result__));

extern void free (void *__ptr) throw ();




extern void cfree (void *__ptr) throw ();



# 1 "/usr/include/alloca.h" 1 3 4
# 25 "/usr/include/alloca.h" 3 4
# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.6.3/include/stddef.h" 1 3 4
# 26 "/usr/include/alloca.h" 2 3 4

extern "C" {





extern void *alloca (size_t __size) throw ();





}
# 498 "/usr/include/stdlib.h" 2 3 4





extern void *valloc (size_t __size) throw () __attribute__ ((__malloc__)) ;




extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     throw () __attribute__ ((__nonnull__ (1))) ;




extern void abort (void) throw () __attribute__ ((__noreturn__));



extern int atexit (void (*__func) (void)) throw () __attribute__ ((__nonnull__ (1)));






extern "C++" int at_quick_exit (void (*__func) (void))
     throw () __asm ("at_quick_exit") __attribute__ ((__nonnull__ (1)));









extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     throw () __attribute__ ((__nonnull__ (1)));






extern void exit (int __status) throw () __attribute__ ((__noreturn__));







extern void quick_exit (int __status) throw () __attribute__ ((__noreturn__));







extern void _Exit (int __status) throw () __attribute__ ((__noreturn__));






extern char *getenv (__const char *__name) throw () __attribute__ ((__nonnull__ (1))) ;




extern char *__secure_getenv (__const char *__name)
     throw () __attribute__ ((__nonnull__ (1))) ;





extern int putenv (char *__string) throw () __attribute__ ((__nonnull__ (1)));





extern int setenv (__const char *__name, __const char *__value, int __replace)
     throw () __attribute__ ((__nonnull__ (2)));


extern int unsetenv (__const char *__name) throw () __attribute__ ((__nonnull__ (1)));






extern int clearenv (void) throw ();
# 606 "/usr/include/stdlib.h" 3 4
extern char *mktemp (char *__template) throw () __attribute__ ((__nonnull__ (1))) ;
# 620 "/usr/include/stdlib.h" 3 4
extern int mkstemp (char *__template) __attribute__ ((__nonnull__ (1))) ;
# 630 "/usr/include/stdlib.h" 3 4
extern int mkstemp64 (char *__template) __attribute__ ((__nonnull__ (1))) ;
# 642 "/usr/include/stdlib.h" 3 4
extern int mkstemps (char *__template, int __suffixlen) __attribute__ ((__nonnull__ (1))) ;
# 652 "/usr/include/stdlib.h" 3 4
extern int mkstemps64 (char *__template, int __suffixlen)
     __attribute__ ((__nonnull__ (1))) ;
# 663 "/usr/include/stdlib.h" 3 4
extern char *mkdtemp (char *__template) throw () __attribute__ ((__nonnull__ (1))) ;
# 674 "/usr/include/stdlib.h" 3 4
extern int mkostemp (char *__template, int __flags) __attribute__ ((__nonnull__ (1))) ;
# 684 "/usr/include/stdlib.h" 3 4
extern int mkostemp64 (char *__template, int __flags) __attribute__ ((__nonnull__ (1))) ;
# 694 "/usr/include/stdlib.h" 3 4
extern int mkostemps (char *__template, int __suffixlen, int __flags)
     __attribute__ ((__nonnull__ (1))) ;
# 706 "/usr/include/stdlib.h" 3 4
extern int mkostemps64 (char *__template, int __suffixlen, int __flags)
     __attribute__ ((__nonnull__ (1))) ;









extern int system (__const char *__command) ;






extern char *canonicalize_file_name (__const char *__name)
     throw () __attribute__ ((__nonnull__ (1))) ;
# 734 "/usr/include/stdlib.h" 3 4
extern char *realpath (__const char *__restrict __name,
         char *__restrict __resolved) throw () ;






typedef int (*__compar_fn_t) (__const void *, __const void *);


typedef __compar_fn_t comparison_fn_t;



typedef int (*__compar_d_fn_t) (__const void *, __const void *, void *);





extern void *bsearch (__const void *__key, __const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     __attribute__ ((__nonnull__ (1, 2, 5))) ;



extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) __attribute__ ((__nonnull__ (1, 4)));

extern void qsort_r (void *__base, size_t __nmemb, size_t __size,
       __compar_d_fn_t __compar, void *__arg)
  __attribute__ ((__nonnull__ (1, 4)));




extern int abs (int __x) throw () __attribute__ ((__const__)) ;
extern long int labs (long int __x) throw () __attribute__ ((__const__)) ;



__extension__ extern long long int llabs (long long int __x)
     throw () __attribute__ ((__const__)) ;







extern div_t div (int __numer, int __denom)
     throw () __attribute__ ((__const__)) ;
extern ldiv_t ldiv (long int __numer, long int __denom)
     throw () __attribute__ ((__const__)) ;




__extension__ extern lldiv_t lldiv (long long int __numer,
        long long int __denom)
     throw () __attribute__ ((__const__)) ;

# 808 "/usr/include/stdlib.h" 3 4
extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) throw () __attribute__ ((__nonnull__ (3, 4))) ;




extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) throw () __attribute__ ((__nonnull__ (3, 4))) ;




extern char *gcvt (double __value, int __ndigit, char *__buf)
     throw () __attribute__ ((__nonnull__ (3))) ;




extern char *qecvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     throw () __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qfcvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     throw () __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     throw () __attribute__ ((__nonnull__ (3))) ;




extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) throw () __attribute__ ((__nonnull__ (3, 4, 5)));
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) throw () __attribute__ ((__nonnull__ (3, 4, 5)));

extern int qecvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     throw () __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qfcvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     throw () __attribute__ ((__nonnull__ (3, 4, 5)));







extern int mblen (__const char *__s, size_t __n) throw () ;


extern int mbtowc (wchar_t *__restrict __pwc,
     __const char *__restrict __s, size_t __n) throw () ;


extern int wctomb (char *__s, wchar_t __wchar) throw () ;



extern size_t mbstowcs (wchar_t *__restrict __pwcs,
   __const char *__restrict __s, size_t __n) throw ();

extern size_t wcstombs (char *__restrict __s,
   __const wchar_t *__restrict __pwcs, size_t __n)
     throw ();








extern int rpmatch (__const char *__response) throw () __attribute__ ((__nonnull__ (1))) ;
# 896 "/usr/include/stdlib.h" 3 4
extern int getsubopt (char **__restrict __optionp,
        char *__const *__restrict __tokens,
        char **__restrict __valuep)
     throw () __attribute__ ((__nonnull__ (1, 2, 3))) ;





extern void setkey (__const char *__key) throw () __attribute__ ((__nonnull__ (1)));







extern int posix_openpt (int __oflag) ;







extern int grantpt (int __fd) throw ();



extern int unlockpt (int __fd) throw ();




extern char *ptsname (int __fd) throw () ;






extern int ptsname_r (int __fd, char *__buf, size_t __buflen)
     throw () __attribute__ ((__nonnull__ (2)));


extern int getpt (void);






extern int getloadavg (double __loadavg[], int __nelem)
     throw () __attribute__ ((__nonnull__ (1)));
# 964 "/usr/include/stdlib.h" 3 4
}
# 36 "/usr/local/include/glyr/types.h" 2 3
# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.6.3/include/stdbool.h" 1 3 4
# 37 "/usr/local/include/glyr/types.h" 2 3
# 1 "/usr/include/sqlite3.h" 1 3 4
# 35 "/usr/include/sqlite3.h" 3 4
# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.6.3/include/stdarg.h" 1 3 4
# 40 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.6.3/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 102 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.6.3/include/stdarg.h" 3 4
typedef __gnuc_va_list va_list;
# 36 "/usr/include/sqlite3.h" 2 3 4





extern "C" {
# 144 "/usr/include/sqlite3.h" 3 4
 extern const char sqlite3_version[];
 const char *sqlite3_libversion(void);
 const char *sqlite3_sourceid(void);
 int sqlite3_libversion_number(void);
# 172 "/usr/include/sqlite3.h" 3 4
 int sqlite3_compileoption_used(const char *zOptName);
 const char *sqlite3_compileoption_get(int N);
# 212 "/usr/include/sqlite3.h" 3 4
 int sqlite3_threadsafe(void);
# 227 "/usr/include/sqlite3.h" 3 4
typedef struct sqlite3 sqlite3;
# 252 "/usr/include/sqlite3.h" 3 4
  typedef long long int sqlite_int64;
  typedef unsigned long long int sqlite_uint64;

typedef sqlite_int64 sqlite3_int64;
typedef sqlite_uint64 sqlite3_uint64;
# 290 "/usr/include/sqlite3.h" 3 4
 int sqlite3_close(sqlite3 *);






typedef int (*sqlite3_callback)(void*,int,char**, char**);
# 360 "/usr/include/sqlite3.h" 3 4
 int sqlite3_exec(
  sqlite3*,
  const char *sql,
  int (*callback)(void*,int,char**,char**),
  void *,
  char **errmsg
);
# 586 "/usr/include/sqlite3.h" 3 4
typedef struct sqlite3_file sqlite3_file;
struct sqlite3_file {
  const struct sqlite3_io_methods *pMethods;
};
# 681 "/usr/include/sqlite3.h" 3 4
typedef struct sqlite3_io_methods sqlite3_io_methods;
struct sqlite3_io_methods {
  int iVersion;
  int (*xClose)(sqlite3_file*);
  int (*xRead)(sqlite3_file*, void*, int iAmt, sqlite3_int64 iOfst);
  int (*xWrite)(sqlite3_file*, const void*, int iAmt, sqlite3_int64 iOfst);
  int (*xTruncate)(sqlite3_file*, sqlite3_int64 size);
  int (*xSync)(sqlite3_file*, int flags);
  int (*xFileSize)(sqlite3_file*, sqlite3_int64 *pSize);
  int (*xLock)(sqlite3_file*, int);
  int (*xUnlock)(sqlite3_file*, int);
  int (*xCheckReservedLock)(sqlite3_file*, int *pResOut);
  int (*xFileControl)(sqlite3_file*, int op, void *pArg);
  int (*xSectorSize)(sqlite3_file*);
  int (*xDeviceCharacteristics)(sqlite3_file*);

  int (*xShmMap)(sqlite3_file*, int iPg, int pgsz, int, void volatile**);
  int (*xShmLock)(sqlite3_file*, int offset, int n, int flags);
  void (*xShmBarrier)(sqlite3_file*);
  int (*xShmUnmap)(sqlite3_file*, int deleteFlag);


};
# 829 "/usr/include/sqlite3.h" 3 4
typedef struct sqlite3_mutex sqlite3_mutex;
# 988 "/usr/include/sqlite3.h" 3 4
typedef struct sqlite3_vfs sqlite3_vfs;
typedef void (*sqlite3_syscall_ptr)(void);
struct sqlite3_vfs {
  int iVersion;
  int szOsFile;
  int mxPathname;
  sqlite3_vfs *pNext;
  const char *zName;
  void *pAppData;
  int (*xOpen)(sqlite3_vfs*, const char *zName, sqlite3_file*,
               int flags, int *pOutFlags);
  int (*xDelete)(sqlite3_vfs*, const char *zName, int syncDir);
  int (*xAccess)(sqlite3_vfs*, const char *zName, int flags, int *pResOut);
  int (*xFullPathname)(sqlite3_vfs*, const char *zName, int nOut, char *zOut);
  void *(*xDlOpen)(sqlite3_vfs*, const char *zFilename);
  void (*xDlError)(sqlite3_vfs*, int nByte, char *zErrMsg);
  void (*(*xDlSym)(sqlite3_vfs*,void*, const char *zSymbol))(void);
  void (*xDlClose)(sqlite3_vfs*, void*);
  int (*xRandomness)(sqlite3_vfs*, int nByte, char *zOut);
  int (*xSleep)(sqlite3_vfs*, int microseconds);
  int (*xCurrentTime)(sqlite3_vfs*, double*);
  int (*xGetLastError)(sqlite3_vfs*, int, char *);




  int (*xCurrentTimeInt64)(sqlite3_vfs*, sqlite3_int64*);




  int (*xSetSystemCall)(sqlite3_vfs*, const char *zName, sqlite3_syscall_ptr);
  sqlite3_syscall_ptr (*xGetSystemCall)(sqlite3_vfs*, const char *zName);
  const char *(*xNextSystemCall)(sqlite3_vfs*, const char *zName);





};
# 1166 "/usr/include/sqlite3.h" 3 4
 int sqlite3_initialize(void);
 int sqlite3_shutdown(void);
 int sqlite3_os_init(void);
 int sqlite3_os_end(void);
# 1200 "/usr/include/sqlite3.h" 3 4
 int sqlite3_config(int, ...);
# 1218 "/usr/include/sqlite3.h" 3 4
 int sqlite3_db_config(sqlite3*, int op, ...);
# 1283 "/usr/include/sqlite3.h" 3 4
typedef struct sqlite3_mem_methods sqlite3_mem_methods;
struct sqlite3_mem_methods {
  void *(*xMalloc)(int);
  void (*xFree)(void*);
  void *(*xRealloc)(void*,int);
  int (*xSize)(void*);
  int (*xRoundup)(int);
  int (*xInit)(void*);
  void (*xShutdown)(void*);
  void *pAppData;
};
# 1610 "/usr/include/sqlite3.h" 3 4
 int sqlite3_extended_result_codes(sqlite3*, int onoff);
# 1659 "/usr/include/sqlite3.h" 3 4
 sqlite3_int64 sqlite3_last_insert_rowid(sqlite3*);
# 1713 "/usr/include/sqlite3.h" 3 4
 int sqlite3_changes(sqlite3*);
# 1739 "/usr/include/sqlite3.h" 3 4
 int sqlite3_total_changes(sqlite3*);
# 1778 "/usr/include/sqlite3.h" 3 4
 void sqlite3_interrupt(sqlite3*);
# 1813 "/usr/include/sqlite3.h" 3 4
 int sqlite3_complete(const char *sql);
 int sqlite3_complete16(const void *sql);
# 1880 "/usr/include/sqlite3.h" 3 4
 int sqlite3_busy_handler(sqlite3*, int(*)(void*,int), void*);
# 1900 "/usr/include/sqlite3.h" 3 4
 int sqlite3_busy_timeout(sqlite3*, int ms);
# 1974 "/usr/include/sqlite3.h" 3 4
 int sqlite3_get_table(
  sqlite3 *db,
  const char *zSql,
  char ***pazResult,
  int *pnRow,
  int *pnColumn,
  char **pzErrmsg
);
 void sqlite3_free_table(char **result);
# 2078 "/usr/include/sqlite3.h" 3 4
 char *sqlite3_mprintf(const char*,...);
 char *sqlite3_vmprintf(const char*, va_list);
 char *sqlite3_snprintf(int,char*,const char*, ...);
 char *sqlite3_vsnprintf(int,char*,const char*, va_list);
# 2153 "/usr/include/sqlite3.h" 3 4
 void *sqlite3_malloc(int);
 void *sqlite3_realloc(void*, int);
 void sqlite3_free(void*);
# 2180 "/usr/include/sqlite3.h" 3 4
 sqlite3_int64 sqlite3_memory_used(void);
 sqlite3_int64 sqlite3_memory_highwater(int resetFlag);
# 2201 "/usr/include/sqlite3.h" 3 4
 void sqlite3_randomness(int N, void *P);
# 2283 "/usr/include/sqlite3.h" 3 4
 int sqlite3_set_authorizer(
  sqlite3*,
  int (*xAuth)(void*,int,const char*,const char*,const char*,const char*),
  void *pUserData
);
# 2383 "/usr/include/sqlite3.h" 3 4
 void *sqlite3_trace(sqlite3*, void(*xTrace)(void*,const char*), void*);
 void *sqlite3_profile(sqlite3*,
   void(*xProfile)(void*,const char*,sqlite3_uint64), void*);
# 2417 "/usr/include/sqlite3.h" 3 4
 void sqlite3_progress_handler(sqlite3*, int, int(*)(void*), void*);
# 2613 "/usr/include/sqlite3.h" 3 4
 int sqlite3_open(
  const char *filename,
  sqlite3 **ppDb
);
 int sqlite3_open16(
  const void *filename,
  sqlite3 **ppDb
);
 int sqlite3_open_v2(
  const char *filename,
  sqlite3 **ppDb,
  int flags,
  const char *zVfs
);
# 2662 "/usr/include/sqlite3.h" 3 4
 const char *sqlite3_uri_parameter(const char *zFilename, const char *zParam);
 int sqlite3_uri_boolean(const char *zFile, const char *zParam, int bDefault);
 sqlite3_int64 sqlite3_uri_int64(const char*, const char*, sqlite3_int64);
# 2700 "/usr/include/sqlite3.h" 3 4
 int sqlite3_errcode(sqlite3 *db);
 int sqlite3_extended_errcode(sqlite3 *db);
 const char *sqlite3_errmsg(sqlite3*);
 const void *sqlite3_errmsg16(sqlite3*);
# 2729 "/usr/include/sqlite3.h" 3 4
typedef struct sqlite3_stmt sqlite3_stmt;
# 2770 "/usr/include/sqlite3.h" 3 4
 int sqlite3_limit(sqlite3*, int id, int newVal);
# 2917 "/usr/include/sqlite3.h" 3 4
 int sqlite3_prepare(
  sqlite3 *db,
  const char *zSql,
  int nByte,
  sqlite3_stmt **ppStmt,
  const char **pzTail
);
 int sqlite3_prepare_v2(
  sqlite3 *db,
  const char *zSql,
  int nByte,
  sqlite3_stmt **ppStmt,
  const char **pzTail
);
 int sqlite3_prepare16(
  sqlite3 *db,
  const void *zSql,
  int nByte,
  sqlite3_stmt **ppStmt,
  const void **pzTail
);
 int sqlite3_prepare16_v2(
  sqlite3 *db,
  const void *zSql,
  int nByte,
  sqlite3_stmt **ppStmt,
  const void **pzTail
);
# 2953 "/usr/include/sqlite3.h" 3 4
 const char *sqlite3_sql(sqlite3_stmt *pStmt);
# 2984 "/usr/include/sqlite3.h" 3 4
 int sqlite3_stmt_readonly(sqlite3_stmt *pStmt);
# 3003 "/usr/include/sqlite3.h" 3 4
 int sqlite3_stmt_busy(sqlite3_stmt*);
# 3042 "/usr/include/sqlite3.h" 3 4
typedef struct Mem sqlite3_value;
# 3056 "/usr/include/sqlite3.h" 3 4
typedef struct sqlite3_context sqlite3_context;
# 3147 "/usr/include/sqlite3.h" 3 4
 int sqlite3_bind_blob(sqlite3_stmt*, int, const void*, int n, void(*)(void*));
 int sqlite3_bind_double(sqlite3_stmt*, int, double);
 int sqlite3_bind_int(sqlite3_stmt*, int, int);
 int sqlite3_bind_int64(sqlite3_stmt*, int, sqlite3_int64);
 int sqlite3_bind_null(sqlite3_stmt*, int);
 int sqlite3_bind_text(sqlite3_stmt*, int, const char*, int n, void(*)(void*));
 int sqlite3_bind_text16(sqlite3_stmt*, int, const void*, int, void(*)(void*));
 int sqlite3_bind_value(sqlite3_stmt*, int, const sqlite3_value*);
 int sqlite3_bind_zeroblob(sqlite3_stmt*, int, int n);
# 3175 "/usr/include/sqlite3.h" 3 4
 int sqlite3_bind_parameter_count(sqlite3_stmt*);
# 3202 "/usr/include/sqlite3.h" 3 4
 const char *sqlite3_bind_parameter_name(sqlite3_stmt*, int);
# 3218 "/usr/include/sqlite3.h" 3 4
 int sqlite3_bind_parameter_index(sqlite3_stmt*, const char *zName);
# 3227 "/usr/include/sqlite3.h" 3 4
 int sqlite3_clear_bindings(sqlite3_stmt*);
# 3238 "/usr/include/sqlite3.h" 3 4
 int sqlite3_column_count(sqlite3_stmt *pStmt);
# 3266 "/usr/include/sqlite3.h" 3 4
 const char *sqlite3_column_name(sqlite3_stmt*, int N);
 const void *sqlite3_column_name16(sqlite3_stmt*, int N);
# 3314 "/usr/include/sqlite3.h" 3 4
 const char *sqlite3_column_database_name(sqlite3_stmt*,int);
 const void *sqlite3_column_database_name16(sqlite3_stmt*,int);
 const char *sqlite3_column_table_name(sqlite3_stmt*,int);
 const void *sqlite3_column_table_name16(sqlite3_stmt*,int);
 const char *sqlite3_column_origin_name(sqlite3_stmt*,int);
 const void *sqlite3_column_origin_name16(sqlite3_stmt*,int);
# 3350 "/usr/include/sqlite3.h" 3 4
 const char *sqlite3_column_decltype(sqlite3_stmt*,int);
 const void *sqlite3_column_decltype16(sqlite3_stmt*,int);
# 3430 "/usr/include/sqlite3.h" 3 4
 int sqlite3_step(sqlite3_stmt*);
# 3450 "/usr/include/sqlite3.h" 3 4
 int sqlite3_data_count(sqlite3_stmt *pStmt);
# 3646 "/usr/include/sqlite3.h" 3 4
 const void *sqlite3_column_blob(sqlite3_stmt*, int iCol);
 int sqlite3_column_bytes(sqlite3_stmt*, int iCol);
 int sqlite3_column_bytes16(sqlite3_stmt*, int iCol);
 double sqlite3_column_double(sqlite3_stmt*, int iCol);
 int sqlite3_column_int(sqlite3_stmt*, int iCol);
 sqlite3_int64 sqlite3_column_int64(sqlite3_stmt*, int iCol);
 const unsigned char *sqlite3_column_text(sqlite3_stmt*, int iCol);
 const void *sqlite3_column_text16(sqlite3_stmt*, int iCol);
 int sqlite3_column_type(sqlite3_stmt*, int iCol);
 sqlite3_value *sqlite3_column_value(sqlite3_stmt*, int iCol);
# 3682 "/usr/include/sqlite3.h" 3 4
 int sqlite3_finalize(sqlite3_stmt *pStmt);
# 3708 "/usr/include/sqlite3.h" 3 4
 int sqlite3_reset(sqlite3_stmt *pStmt);
# 3798 "/usr/include/sqlite3.h" 3 4
 int sqlite3_create_function(
  sqlite3 *db,
  const char *zFunctionName,
  int nArg,
  int eTextRep,
  void *pApp,
  void (*xFunc)(sqlite3_context*,int,sqlite3_value**),
  void (*xStep)(sqlite3_context*,int,sqlite3_value**),
  void (*xFinal)(sqlite3_context*)
);
 int sqlite3_create_function16(
  sqlite3 *db,
  const void *zFunctionName,
  int nArg,
  int eTextRep,
  void *pApp,
  void (*xFunc)(sqlite3_context*,int,sqlite3_value**),
  void (*xStep)(sqlite3_context*,int,sqlite3_value**),
  void (*xFinal)(sqlite3_context*)
);
 int sqlite3_create_function_v2(
  sqlite3 *db,
  const char *zFunctionName,
  int nArg,
  int eTextRep,
  void *pApp,
  void (*xFunc)(sqlite3_context*,int,sqlite3_value**),
  void (*xStep)(sqlite3_context*,int,sqlite3_value**),
  void (*xFinal)(sqlite3_context*),
  void(*xDestroy)(void*)
);
# 3854 "/usr/include/sqlite3.h" 3 4
 int sqlite3_aggregate_count(sqlite3_context*);
 int sqlite3_expired(sqlite3_stmt*);
 int sqlite3_transfer_bindings(sqlite3_stmt*, sqlite3_stmt*);
 int sqlite3_global_recover(void);
 void sqlite3_thread_cleanup(void);
 int sqlite3_memory_alarm(void(*)(void*,sqlite3_int64,int),void*,sqlite3_int64);
# 3907 "/usr/include/sqlite3.h" 3 4
 const void *sqlite3_value_blob(sqlite3_value*);
 int sqlite3_value_bytes(sqlite3_value*);
 int sqlite3_value_bytes16(sqlite3_value*);
 double sqlite3_value_double(sqlite3_value*);
 int sqlite3_value_int(sqlite3_value*);
 sqlite3_int64 sqlite3_value_int64(sqlite3_value*);
 const unsigned char *sqlite3_value_text(sqlite3_value*);
 const void *sqlite3_value_text16(sqlite3_value*);
 const void *sqlite3_value_text16le(sqlite3_value*);
 const void *sqlite3_value_text16be(sqlite3_value*);
 int sqlite3_value_type(sqlite3_value*);
 int sqlite3_value_numeric_type(sqlite3_value*);
# 3959 "/usr/include/sqlite3.h" 3 4
 void *sqlite3_aggregate_context(sqlite3_context*, int nBytes);
# 3973 "/usr/include/sqlite3.h" 3 4
 void *sqlite3_user_data(sqlite3_context*);
# 3984 "/usr/include/sqlite3.h" 3 4
 sqlite3 *sqlite3_context_db_handle(sqlite3_context*);
# 4028 "/usr/include/sqlite3.h" 3 4
 void *sqlite3_get_auxdata(sqlite3_context*, int N);
 void sqlite3_set_auxdata(sqlite3_context*, int N, void*, void (*)(void*));
# 4046 "/usr/include/sqlite3.h" 3 4
typedef void (*sqlite3_destructor_type)(void*);
# 4160 "/usr/include/sqlite3.h" 3 4
 void sqlite3_result_blob(sqlite3_context*, const void*, int, void(*)(void*));
 void sqlite3_result_double(sqlite3_context*, double);
 void sqlite3_result_error(sqlite3_context*, const char*, int);
 void sqlite3_result_error16(sqlite3_context*, const void*, int);
 void sqlite3_result_error_toobig(sqlite3_context*);
 void sqlite3_result_error_nomem(sqlite3_context*);
 void sqlite3_result_error_code(sqlite3_context*, int);
 void sqlite3_result_int(sqlite3_context*, int);
 void sqlite3_result_int64(sqlite3_context*, sqlite3_int64);
 void sqlite3_result_null(sqlite3_context*);
 void sqlite3_result_text(sqlite3_context*, const char*, int, void(*)(void*));
 void sqlite3_result_text16(sqlite3_context*, const void*, int, void(*)(void*));
 void sqlite3_result_text16le(sqlite3_context*, const void*, int,void(*)(void*));
 void sqlite3_result_text16be(sqlite3_context*, const void*, int,void(*)(void*));
 void sqlite3_result_value(sqlite3_context*, sqlite3_value*);
 void sqlite3_result_zeroblob(sqlite3_context*, int n);
# 4256 "/usr/include/sqlite3.h" 3 4
 int sqlite3_create_collation(
  sqlite3*,
  const char *zName,
  int eTextRep,
  void *pArg,
  int(*xCompare)(void*,int,const void*,int,const void*)
);
 int sqlite3_create_collation_v2(
  sqlite3*,
  const char *zName,
  int eTextRep,
  void *pArg,
  int(*xCompare)(void*,int,const void*,int,const void*),
  void(*xDestroy)(void*)
);
 int sqlite3_create_collation16(
  sqlite3*,
  const void *zName,
  int eTextRep,
  void *pArg,
  int(*xCompare)(void*,int,const void*,int,const void*)
);
# 4305 "/usr/include/sqlite3.h" 3 4
 int sqlite3_collation_needed(
  sqlite3*,
  void*,
  void(*)(void*,sqlite3*,int eTextRep,const char*)
);
 int sqlite3_collation_needed16(
  sqlite3*,
  void*,
  void(*)(void*,sqlite3*,int eTextRep,const void*)
);
# 4378 "/usr/include/sqlite3.h" 3 4
 int sqlite3_sleep(int);
# 4409 "/usr/include/sqlite3.h" 3 4
 extern char *sqlite3_temp_directory;
# 4432 "/usr/include/sqlite3.h" 3 4
 int sqlite3_get_autocommit(sqlite3*);
# 4444 "/usr/include/sqlite3.h" 3 4
 sqlite3 *sqlite3_db_handle(sqlite3_stmt*);
# 4460 "/usr/include/sqlite3.h" 3 4
 const char *sqlite3_db_filename(sqlite3 *db, const char *zDbName);
# 4475 "/usr/include/sqlite3.h" 3 4
 sqlite3_stmt *sqlite3_next_stmt(sqlite3 *pDb, sqlite3_stmt *pStmt);
# 4523 "/usr/include/sqlite3.h" 3 4
 void *sqlite3_commit_hook(sqlite3*, int(*)(void*), void*);
 void *sqlite3_rollback_hook(sqlite3*, void(*)(void *), void*);
# 4572 "/usr/include/sqlite3.h" 3 4
 void *sqlite3_update_hook(
  sqlite3*,
  void(*)(void *,int ,char const *,char const *,sqlite3_int64),
  void*
);
# 4605 "/usr/include/sqlite3.h" 3 4
 int sqlite3_enable_shared_cache(int);
# 4621 "/usr/include/sqlite3.h" 3 4
 int sqlite3_release_memory(int);
# 4634 "/usr/include/sqlite3.h" 3 4
 int sqlite3_db_release_memory(sqlite3*);
# 4686 "/usr/include/sqlite3.h" 3 4
 sqlite3_int64 sqlite3_soft_heap_limit64(sqlite3_int64 N);
# 4697 "/usr/include/sqlite3.h" 3 4
 void sqlite3_soft_heap_limit(int N);
# 4762 "/usr/include/sqlite3.h" 3 4
 int sqlite3_table_column_metadata(
  sqlite3 *db,
  const char *zDbName,
  const char *zTableName,
  const char *zColumnName,
  char const **pzDataType,
  char const **pzCollSeq,
  int *pNotNull,
  int *pPrimaryKey,
  int *pAutoinc
);
# 4799 "/usr/include/sqlite3.h" 3 4
 int sqlite3_load_extension(
  sqlite3 *db,
  const char *zFile,
  const char *zProc,
  char **pzErrMsg
);
# 4819 "/usr/include/sqlite3.h" 3 4
 int sqlite3_enable_load_extension(sqlite3 *db, int onoff);
# 4856 "/usr/include/sqlite3.h" 3 4
 int sqlite3_auto_extension(void (*xEntryPoint)(void));







 void sqlite3_reset_auto_extension(void);
# 4878 "/usr/include/sqlite3.h" 3 4
typedef struct sqlite3_vtab sqlite3_vtab;
typedef struct sqlite3_index_info sqlite3_index_info;
typedef struct sqlite3_vtab_cursor sqlite3_vtab_cursor;
typedef struct sqlite3_module sqlite3_module;
# 4899 "/usr/include/sqlite3.h" 3 4
struct sqlite3_module {
  int iVersion;
  int (*xCreate)(sqlite3*, void *pAux,
               int argc, const char *const*argv,
               sqlite3_vtab **ppVTab, char**);
  int (*xConnect)(sqlite3*, void *pAux,
               int argc, const char *const*argv,
               sqlite3_vtab **ppVTab, char**);
  int (*xBestIndex)(sqlite3_vtab *pVTab, sqlite3_index_info*);
  int (*xDisconnect)(sqlite3_vtab *pVTab);
  int (*xDestroy)(sqlite3_vtab *pVTab);
  int (*xOpen)(sqlite3_vtab *pVTab, sqlite3_vtab_cursor **ppCursor);
  int (*xClose)(sqlite3_vtab_cursor*);
  int (*xFilter)(sqlite3_vtab_cursor*, int idxNum, const char *idxStr,
                int argc, sqlite3_value **argv);
  int (*xNext)(sqlite3_vtab_cursor*);
  int (*xEof)(sqlite3_vtab_cursor*);
  int (*xColumn)(sqlite3_vtab_cursor*, sqlite3_context*, int);
  int (*xRowid)(sqlite3_vtab_cursor*, sqlite3_int64 *pRowid);
  int (*xUpdate)(sqlite3_vtab *, int, sqlite3_value **, sqlite3_int64 *);
  int (*xBegin)(sqlite3_vtab *pVTab);
  int (*xSync)(sqlite3_vtab *pVTab);
  int (*xCommit)(sqlite3_vtab *pVTab);
  int (*xRollback)(sqlite3_vtab *pVTab);
  int (*xFindFunction)(sqlite3_vtab *pVtab, int nArg, const char *zName,
                       void (**pxFunc)(sqlite3_context*,int,sqlite3_value**),
                       void **ppArg);
  int (*xRename)(sqlite3_vtab *pVtab, const char *zNew);


  int (*xSavepoint)(sqlite3_vtab *pVTab, int);
  int (*xRelease)(sqlite3_vtab *pVTab, int);
  int (*xRollbackTo)(sqlite3_vtab *pVTab, int);
};
# 4987 "/usr/include/sqlite3.h" 3 4
struct sqlite3_index_info {

  int nConstraint;
  struct sqlite3_index_constraint {
     int iColumn;
     unsigned char op;
     unsigned char usable;
     int iTermOffset;
  } *aConstraint;
  int nOrderBy;
  struct sqlite3_index_orderby {
     int iColumn;
     unsigned char desc;
  } *aOrderBy;

  struct sqlite3_index_constraint_usage {
    int argvIndex;
    unsigned char omit;
  } *aConstraintUsage;
  int idxNum;
  char *idxStr;
  int needToFreeIdxStr;
  int orderByConsumed;
  double estimatedCost;
};
# 5053 "/usr/include/sqlite3.h" 3 4
 int sqlite3_create_module(
  sqlite3 *db,
  const char *zName,
  const sqlite3_module *p,
  void *pClientData
);
 int sqlite3_create_module_v2(
  sqlite3 *db,
  const char *zName,
  const sqlite3_module *p,
  void *pClientData,
  void(*xDestroy)(void*)
);
# 5085 "/usr/include/sqlite3.h" 3 4
struct sqlite3_vtab {
  const sqlite3_module *pModule;
  int nRef;
  char *zErrMsg;

};
# 5109 "/usr/include/sqlite3.h" 3 4
struct sqlite3_vtab_cursor {
  sqlite3_vtab *pVtab;

};
# 5122 "/usr/include/sqlite3.h" 3 4
 int sqlite3_declare_vtab(sqlite3*, const char *zSQL);
# 5140 "/usr/include/sqlite3.h" 3 4
 int sqlite3_overload_function(sqlite3*, const char *zFuncName, int nArg);
# 5164 "/usr/include/sqlite3.h" 3 4
typedef struct sqlite3_blob sqlite3_blob;
# 5222 "/usr/include/sqlite3.h" 3 4
 int sqlite3_blob_open(
  sqlite3*,
  const char *zDb,
  const char *zTable,
  const char *zColumn,
  sqlite3_int64 iRow,
  int flags,
  sqlite3_blob **ppBlob
);
# 5254 "/usr/include/sqlite3.h" 3 4
 int sqlite3_blob_reopen(sqlite3_blob *, sqlite3_int64);
# 5278 "/usr/include/sqlite3.h" 3 4
 int sqlite3_blob_close(sqlite3_blob *);
# 5293 "/usr/include/sqlite3.h" 3 4
 int sqlite3_blob_bytes(sqlite3_blob *);
# 5321 "/usr/include/sqlite3.h" 3 4
 int sqlite3_blob_read(sqlite3_blob *, void *Z, int N, int iOffset);
# 5359 "/usr/include/sqlite3.h" 3 4
 int sqlite3_blob_write(sqlite3_blob *, const void *z, int n, int iOffset);
# 5390 "/usr/include/sqlite3.h" 3 4
 sqlite3_vfs *sqlite3_vfs_find(const char *zVfsName);
 int sqlite3_vfs_register(sqlite3_vfs*, int makeDflt);
 int sqlite3_vfs_unregister(sqlite3_vfs*);
# 5508 "/usr/include/sqlite3.h" 3 4
 sqlite3_mutex *sqlite3_mutex_alloc(int);
 void sqlite3_mutex_free(sqlite3_mutex*);
 void sqlite3_mutex_enter(sqlite3_mutex*);
 int sqlite3_mutex_try(sqlite3_mutex*);
 void sqlite3_mutex_leave(sqlite3_mutex*);
# 5579 "/usr/include/sqlite3.h" 3 4
typedef struct sqlite3_mutex_methods sqlite3_mutex_methods;
struct sqlite3_mutex_methods {
  int (*xMutexInit)(void);
  int (*xMutexEnd)(void);
  sqlite3_mutex *(*xMutexAlloc)(int);
  void (*xMutexFree)(sqlite3_mutex *);
  void (*xMutexEnter)(sqlite3_mutex *);
  int (*xMutexTry)(sqlite3_mutex *);
  void (*xMutexLeave)(sqlite3_mutex *);
  int (*xMutexHeld)(sqlite3_mutex *);
  int (*xMutexNotheld)(sqlite3_mutex *);
};
# 5622 "/usr/include/sqlite3.h" 3 4
 int sqlite3_mutex_held(sqlite3_mutex*);
 int sqlite3_mutex_notheld(sqlite3_mutex*);
# 5656 "/usr/include/sqlite3.h" 3 4
 sqlite3_mutex *sqlite3_db_mutex(sqlite3*);
# 5690 "/usr/include/sqlite3.h" 3 4
 int sqlite3_file_control(sqlite3*, const char *zDbName, int op, void*);
# 5709 "/usr/include/sqlite3.h" 3 4
 int sqlite3_test_control(int op, ...);
# 5769 "/usr/include/sqlite3.h" 3 4
 int sqlite3_status(int op, int *pCurrent, int *pHighwater, int resetFlag);
# 5887 "/usr/include/sqlite3.h" 3 4
 int sqlite3_db_status(sqlite3*, int op, int *pCur, int *pHiwtr, int resetFlg);
# 5997 "/usr/include/sqlite3.h" 3 4
 int sqlite3_stmt_status(sqlite3_stmt*, int op,int resetFlg);
# 6042 "/usr/include/sqlite3.h" 3 4
typedef struct sqlite3_pcache sqlite3_pcache;
# 6054 "/usr/include/sqlite3.h" 3 4
typedef struct sqlite3_pcache_page sqlite3_pcache_page;
struct sqlite3_pcache_page {
  void *pBuf;
  void *pExtra;
};
# 6219 "/usr/include/sqlite3.h" 3 4
typedef struct sqlite3_pcache_methods2 sqlite3_pcache_methods2;
struct sqlite3_pcache_methods2 {
  int iVersion;
  void *pArg;
  int (*xInit)(void*);
  void (*xShutdown)(void*);
  sqlite3_pcache *(*xCreate)(int szPage, int szExtra, int bPurgeable);
  void (*xCachesize)(sqlite3_pcache*, int nCachesize);
  int (*xPagecount)(sqlite3_pcache*);
  sqlite3_pcache_page *(*xFetch)(sqlite3_pcache*, unsigned key, int createFlag);
  void (*xUnpin)(sqlite3_pcache*, sqlite3_pcache_page*, int discard);
  void (*xRekey)(sqlite3_pcache*, sqlite3_pcache_page*,
      unsigned oldKey, unsigned newKey);
  void (*xTruncate)(sqlite3_pcache*, unsigned iLimit);
  void (*xDestroy)(sqlite3_pcache*);
  void (*xShrink)(sqlite3_pcache*);
};






typedef struct sqlite3_pcache_methods sqlite3_pcache_methods;
struct sqlite3_pcache_methods {
  void *pArg;
  int (*xInit)(void*);
  void (*xShutdown)(void*);
  sqlite3_pcache *(*xCreate)(int szPage, int bPurgeable);
  void (*xCachesize)(sqlite3_pcache*, int nCachesize);
  int (*xPagecount)(sqlite3_pcache*);
  void *(*xFetch)(sqlite3_pcache*, unsigned key, int createFlag);
  void (*xUnpin)(sqlite3_pcache*, void*, int discard);
  void (*xRekey)(sqlite3_pcache*, void*, unsigned oldKey, unsigned newKey);
  void (*xTruncate)(sqlite3_pcache*, unsigned iLimit);
  void (*xDestroy)(sqlite3_pcache*);
};
# 6268 "/usr/include/sqlite3.h" 3 4
typedef struct sqlite3_backup sqlite3_backup;
# 6452 "/usr/include/sqlite3.h" 3 4
 sqlite3_backup *sqlite3_backup_init(
  sqlite3 *pDest,
  const char *zDestName,
  sqlite3 *pSource,
  const char *zSourceName
);
 int sqlite3_backup_step(sqlite3_backup *p, int nPage);
 int sqlite3_backup_finish(sqlite3_backup *p);
 int sqlite3_backup_remaining(sqlite3_backup *p);
 int sqlite3_backup_pagecount(sqlite3_backup *p);
# 6577 "/usr/include/sqlite3.h" 3 4
 int sqlite3_unlock_notify(
  sqlite3 *pBlocked,
  void (*xNotify)(void **apArg, int nArg),
  void *pNotifyArg
);
# 6592 "/usr/include/sqlite3.h" 3 4
 int sqlite3_strnicmp(const char *, const char *, int);
# 6615 "/usr/include/sqlite3.h" 3 4
 void sqlite3_log(int iErrCode, const char *zFormat, ...);
# 6652 "/usr/include/sqlite3.h" 3 4
 void *sqlite3_wal_hook(
  sqlite3*,
  int(*)(void *,sqlite3*,const char*,int),
  void*
);
# 6683 "/usr/include/sqlite3.h" 3 4
 int sqlite3_wal_autocheckpoint(sqlite3 *db, int N);
# 6701 "/usr/include/sqlite3.h" 3 4
 int sqlite3_wal_checkpoint(sqlite3 *db, const char *zDb);
# 6773 "/usr/include/sqlite3.h" 3 4
 int sqlite3_wal_checkpoint_v2(
  sqlite3 *db,
  const char *zDb,
  int eMode,
  int *pnLog,
  int *pnCkpt
);
# 6807 "/usr/include/sqlite3.h" 3 4
 int sqlite3_vtab_config(sqlite3*, int op, ...);
# 6860 "/usr/include/sqlite3.h" 3 4
 int sqlite3_vtab_on_conflict(sqlite3 *);
# 6890 "/usr/include/sqlite3.h" 3 4
}
# 6912 "/usr/include/sqlite3.h" 3 4
extern "C" {


typedef struct sqlite3_rtree_geometry sqlite3_rtree_geometry;







 int sqlite3_rtree_geometry_callback(
  sqlite3 *db,
  const char *zGeom,
  int (*xGeom)(sqlite3_rtree_geometry *, int nCoord, double *aCoord, int *pRes),
  void *pContext
);






struct sqlite3_rtree_geometry {
  void *pContext;
  int nParam;
  double *aParam;
  void *pUser;
  void (*xDelUser)(void *);
};



}
# 38 "/usr/local/include/glyr/types.h" 2 3


# 1 "/usr/local/include/glyr/config.h" 1 3
# 41 "/usr/local/include/glyr/types.h" 2 3
# 100 "/usr/local/include/glyr/types.h" 3
typedef enum
{
    GLYRE_UNKNOWN = 0,
    GLYRE_OK,
    GLYRE_BAD_OPTION,
    GLYRE_BAD_VALUE,
    GLYRE_EMPTY_STRUCT,
    GLYRE_NO_PROVIDER,
    GLYRE_UNKNOWN_GET,
    GLYRE_INSUFF_DATA,
    GLYRE_SKIP,
    GLYRE_STOP_POST,
    GLYRE_STOP_PRE,
    GLYRE_NO_INIT,
    GLYRE_WAS_STOPPED
} GLYR_ERROR;
# 144 "/usr/local/include/glyr/types.h" 3
typedef enum
{
    GLYR_GET_UNSURE,
    GLYR_GET_COVERART,
    GLYR_GET_LYRICS,
    GLYR_GET_ARTIST_PHOTOS,
    GLYR_GET_ARTISTBIO,
    GLYR_GET_SIMILIAR_ARTISTS,
    GLYR_GET_SIMILIAR_SONGS,
    GLYR_GET_ALBUM_REVIEW,
    GLYR_GET_TRACKLIST,
    GLYR_GET_TAGS,
    GLYR_GET_RELATIONS,
    GLYR_GET_ALBUMLIST,
    GLYR_GET_GUITARTABS,
    GLYR_GET_BACKDROPS,
    GLYR_GET_ANY
} GLYR_GET_TYPE;
# 195 "/usr/local/include/glyr/types.h" 3
typedef enum
{
    GLYR_TYPE_NOIDEA,
    GLYR_TYPE_LYRICS,
    GLYR_TYPE_ALBUM_REVIEW,
    GLYR_TYPE_ARTIST_PHOTO,
    GLYR_TYPE_COVERART,
    GLYR_TYPE_ARTISTBIO,
    GLYR_TYPE_SIMILAR_ARTIST,
    GLYR_TYPE_SIMILAR_SONG,
    GLYR_TYPE_ALBUMLIST,
    GLYR_TYPE_TAG,
    GLYR_TYPE_TAG_ARTIST,
    GLYR_TYPE_TAG_ALBUM,
    GLYR_TYPE_TAG_TITLE,
    GLYR_TYPE_RELATION,
    GLYR_TYPE_IMG_URL,
    GLYR_TYPE_TXT_URL,
    GLYR_TYPE_TRACK,
    GLYR_TYPE_GUITARTABS,
    GLYR_TYPE_BACKDROPS
} GLYR_DATA_TYPE;
# 231 "/usr/local/include/glyr/types.h" 3
typedef enum
{
    GLYR_REQUIRES_ARTIST = 1 << 0,
    GLYR_REQUIRES_ALBUM = 1 << 1,
    GLYR_REQUIRES_TITLE = 1 << 2,
    GLYR_OPTIONAL_ARTIST = 1 << 3,
    GLYR_OPTIONAL_ALBUM = 1 << 4,
    GLYR_OPTIONAL_TITLE = 1 << 5
} GLYR_FIELD_REQUIREMENT;
# 263 "/usr/local/include/glyr/types.h" 3
typedef struct _GlyrMemCache {


  char * data;
  size_t size;
  char * dsrc;
  char * prov;
  GLYR_DATA_TYPE type;
  int duration;
  int rating;
  bool is_image;
  char * img_format;
  unsigned char md5sum[16];
  bool cached;
  double timestamp;

  struct _GlyrMemCache * next;
  struct _GlyrMemCache * prev;
} GlyrMemCache;
# 290 "/usr/local/include/glyr/types.h" 3
struct _GlyrDatabase;
typedef struct _GlyrDatabase {

 char * root_path;


 sqlite3 * db_handle;

} GlyrDatabase;
# 335 "/usr/local/include/glyr/types.h" 3
typedef struct _GlyrQuery {

    GLYR_GET_TYPE type;

    int number;
    int plugmax;
    int verbosity;
    size_t fuzzyness;

    int img_min_size;
    int img_max_size;

    int parallel;
    int timeout;
    int redirects;

    bool force_utf8;
    bool download;
    float qsratio;

    bool db_autoread;
    bool db_autowrite;
    GlyrDatabase * local_db;

    bool lang_aware_only;


    volatile int signal_exit;


    char * lang;
    char * proxy;
    char * artist;
    char * album;
    char * title;
    char * from;
    char * allowed_formats;
    char * useragent;
    char * musictree_path;


    struct {
         GLYR_ERROR (* download)(GlyrMemCache * dl, struct _GlyrQuery * s);
         void * user_pointer;
    } callback;



    int itemctr;
    char * info[10];
    bool imagejob;
    long is_initalized;

} GlyrQuery;
# 408 "/usr/local/include/glyr/types.h" 3
typedef struct _GlyrSourceInfo {


  char * name;
  char key;
  GLYR_GET_TYPE type;
  int quality;
  int speed;
  bool lang_aware;

  struct _GlyrSourceInfo * next;
  struct _GlyrSourceInfo * prev;
} GlyrSourceInfo;
# 440 "/usr/local/include/glyr/types.h" 3
typedef struct _GlyrFetcherInfo {


  char * name;
  GLYR_GET_TYPE type;
  GLYR_FIELD_REQUIREMENT reqs;
  GlyrSourceInfo * head;

  struct _GlyrFetcherInfo * next;
  struct _GlyrFetcherInfo * prev;
} GlyrFetcherInfo;
# 462 "/usr/local/include/glyr/types.h" 3
typedef GLYR_ERROR (*DL_callback)(GlyrMemCache * dl, struct _GlyrQuery * s);
# 36 "/usr/local/include/glyr/glyr.h" 2 3


extern "C"
{
# 54 "/usr/local/include/glyr/glyr.h" 3
void glyr_init(void);
# 75 "/usr/local/include/glyr/glyr.h" 3
void glyr_cleanup(void);
# 92 "/usr/local/include/glyr/glyr.h" 3
GlyrMemCache * glyr_get(GlyrQuery * settings, GLYR_ERROR * error, int * length);
# 101 "/usr/local/include/glyr/glyr.h" 3
void glyr_query_init(GlyrQuery * query);
# 110 "/usr/local/include/glyr/glyr.h" 3
void glyr_query_destroy(GlyrQuery * query);
# 127 "/usr/local/include/glyr/glyr.h" 3
void glyr_signal_exit(GlyrQuery * query);
# 136 "/usr/local/include/glyr/glyr.h" 3
void glyr_free_list(GlyrMemCache * head);
# 149 "/usr/local/include/glyr/glyr.h" 3
GlyrMemCache * glyr_cache_new(void);





void glyr_cache_free(GlyrMemCache * cache);
# 167 "/usr/local/include/glyr/glyr.h" 3
GlyrMemCache * glyr_cache_copy(GlyrMemCache * cache);
# 176 "/usr/local/include/glyr/glyr.h" 3
void glyr_cache_set_dsrc(GlyrMemCache * cache, const char * download_source);







void glyr_cache_set_prov(GlyrMemCache * cache, const char * provider);







void glyr_cache_set_img_format(GlyrMemCache * cache, const char * img_format);





void glyr_cache_set_type(GlyrMemCache * cache, GLYR_DATA_TYPE type);





void glyr_cache_set_rating(GlyrMemCache * cache, int rating);
# 219 "/usr/local/include/glyr/glyr.h" 3
void glyr_cache_set_data(GlyrMemCache * cache, const char * data, int len);
# 249 "/usr/local/include/glyr/glyr.h" 3
int glyr_cache_write(GlyrMemCache * cache, const char * path);
# 259 "/usr/local/include/glyr/glyr.h" 3
void glyr_cache_update_md5sum(GlyrMemCache * cache);
# 269 "/usr/local/include/glyr/glyr.h" 3
void glyr_cache_print(GlyrMemCache * cache);
# 300 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_dlcallback(GlyrQuery * settings, DL_callback dl_cb, void * userp);
# 311 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_type(GlyrQuery * s, GLYR_GET_TYPE type);
# 329 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_artist(GlyrQuery * s, char * artist);
# 379 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_album(GlyrQuery * s, char * album);
# 424 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_title(GlyrQuery * s, char * title);
# 439 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_img_minsize(GlyrQuery * s, int size);
# 454 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_img_maxsize(GlyrQuery * s, int size);
# 465 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_parallel(GlyrQuery * s, unsigned long parallel_jobs);
# 476 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_timeout(GlyrQuery * s, unsigned long timeout);
# 487 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_redirects(GlyrQuery * s, unsigned long redirects);
# 498 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_useragent(GlyrQuery * s, const char * useragent);
# 514 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_lang(GlyrQuery * s, char * langcode);
# 526 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_lang_aware_only(GlyrQuery * s, bool lang_aware_only);
# 539 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_number(GlyrQuery * s, unsigned int num);
# 577 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_verbosity(GlyrQuery * s, unsigned int level);
# 608 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_from(GlyrQuery * s, const char * from);
# 622 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_plugmax(GlyrQuery * s, int plugmax);
# 656 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_allowed_formats(GlyrQuery * s, const char * formats);
# 671 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_download(GlyrQuery * s, bool download);
# 719 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_fuzzyness(GlyrQuery * s, int fuzz);
# 734 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_qsratio(GlyrQuery * s, float ratio);
# 761 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_proxy(GlyrQuery * s, const char * proxystring);
# 776 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_force_utf8(GlyrQuery * s, bool force_utf8);
# 806 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_lookup_db(GlyrQuery * s, GlyrDatabase * db);
# 819 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_db_autowrite(GlyrQuery * s, bool write_to_db);
# 839 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_db_autoread(GlyrQuery * s, bool read_from_db);
# 884 "/usr/local/include/glyr/glyr.h" 3
GLYR_ERROR glyr_opt_musictree_path(GlyrQuery * s, const char * musictree_path);
# 896 "/usr/local/include/glyr/glyr.h" 3
GlyrMemCache * glyr_download(const char * url, GlyrQuery * s);
# 906 "/usr/local/include/glyr/glyr.h" 3
const char * glyr_strerror(GLYR_ERROR ID);
# 917 "/usr/local/include/glyr/glyr.h" 3
const char * glyr_version(void);
# 953 "/usr/local/include/glyr/glyr.h" 3
GlyrFetcherInfo * glyr_info_get(void);







void glyr_info_free(GlyrFetcherInfo * info);
# 971 "/usr/local/include/glyr/glyr.h" 3
const char * glyr_data_type_to_string(GLYR_DATA_TYPE type);
# 982 "/usr/local/include/glyr/glyr.h" 3
const char * glyr_get_type_to_string(GLYR_GET_TYPE type);
# 993 "/usr/local/include/glyr/glyr.h" 3
char * glyr_md5sum_to_string(unsigned char * md5sum);
# 1005 "/usr/local/include/glyr/glyr.h" 3
void glyr_string_to_md5sum(const char * string, unsigned char * md5sum);
# 1036 "/usr/local/include/glyr/glyr.h" 3
GLYR_FIELD_REQUIREMENT glyr_get_requirements(GLYR_GET_TYPE type);
# 6 "Request.hh" 2

void request(GLYR_GET_TYPE type);
# 2 "Request.cc" 2

void request(GLYR_GET_TYPE type)
{

}
