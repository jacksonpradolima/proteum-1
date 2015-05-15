
typedef long unsigned int size_t; 
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
typedef long int __fsword_t; 
typedef long int __ssize_t; 
typedef long int __syscall_slong_t; 
typedef unsigned long int __syscall_ulong_t; 
typedef __off64_t __loff_t; 
typedef __quad_t *__qaddr_t; 
typedef char *__caddr_t; 
typedef long int __intptr_t; 
typedef unsigned int __socklen_t; 
struct _IO_FILE; 
typedef struct _IO_FILE FILE; 
typedef struct _IO_FILE __FILE; 
typedef struct
{
  int __count;
  union
  {
    unsigned int __wch;
    char __wchb[4];
  } __value;
} __mbstate_t; 
typedef struct
{
  __off_t __pos;
  __mbstate_t __state;
} _G_fpos_t; 
typedef struct
{
  __off64_t __pos;
  __mbstate_t __state;
} _G_fpos64_t; 
typedef __gnuc_va_list; 
struct _IO_jump_t; 
struct _IO_FILE; 
typedef void _IO_lock_t; 
struct _IO_marker {
  struct _IO_marker *_next;
  struct _IO_FILE *_sbuf;
  int _pos;
}; 
enum __codecvt_result
{
  __codecvt_ok,
  __codecvt_partial,
  __codecvt_error,
  __codecvt_noconv
}; 
struct _IO_FILE {
  int _flags;
  char* _IO_read_ptr;
  char* _IO_read_end;
  char* _IO_read_base;
  char* _IO_write_base;
  char* _IO_write_ptr;
  char* _IO_write_end;
  char* _IO_buf_base;
  char* _IO_buf_end;
  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;
  struct _IO_marker *_markers;
  struct _IO_FILE *_chain;
  int _fileno;
  int _flags2;
  __off_t _old_offset;
  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];
  _IO_lock_t *_lock;
  __off64_t _offset;
  void *__pad1;
  void *__pad2;
  void *__pad3;
  void *__pad4;
  size_t __pad5;
  int _mode;
  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];
}; 
typedef struct _IO_FILE _IO_FILE; 
struct _IO_FILE_plus; 
extern struct _IO_FILE_plus _IO_2_1_stdin_; 
extern struct _IO_FILE_plus _IO_2_1_stdout_; 
extern struct _IO_FILE_plus _IO_2_1_stderr_; 
typedef __ssize_t __io_read_fn (void *__cookie, char *__buf, size_t __nbytes); 
typedef __ssize_t __io_write_fn (void *__cookie, const char *__buf,
     size_t __n); 
typedef int __io_seek_fn (void *__cookie, __off64_t *__pos, int __w); 
typedef int __io_close_fn (void *__cookie); 
extern int __underflow (_IO_FILE *); 
extern int __uflow (_IO_FILE *); 
extern int __overflow (_IO_FILE *, int); 
extern int _IO_getc (_IO_FILE *__fp); 
extern int _IO_putc (int __c, _IO_FILE *__fp); 
extern int _IO_feof (_IO_FILE *__fp) ; 
extern int _IO_ferror (_IO_FILE *__fp) ; 
extern int _IO_peekc_locked (_IO_FILE *__fp); 
extern void _IO_flockfile (_IO_FILE *) ; 
extern void _IO_funlockfile (_IO_FILE *) ; 
extern int _IO_ftrylockfile (_IO_FILE *) ; 
extern int _IO_vfscanf (_IO_FILE * , const char * ,
   __gnuc_va_list, int *); 
extern int _IO_vfprintf (_IO_FILE *, const char *,
    __gnuc_va_list); 
extern __ssize_t _IO_padn (_IO_FILE *, int, __ssize_t); 
extern size_t _IO_sgetn (_IO_FILE *, void *, size_t); 
extern __off64_t _IO_seekoff (_IO_FILE *, __off64_t, int, int); 
extern __off64_t _IO_seekpos (_IO_FILE *, __off64_t, int); 
extern void _IO_free_backup_area (_IO_FILE *) ; 
typedef _G_fpos_t fpos_t; 
extern struct _IO_FILE *stdin; 
extern struct _IO_FILE *stdout; 
extern struct _IO_FILE *stderr; 
extern int remove (const char *__filename) ; 
extern int rename (const char *__old, const char *__new) ; 
extern FILE *tmpfile (void) ; 
extern char *tmpnam (char *__s) ; 
extern int fclose (FILE *__stream); 
extern int fflush (FILE *__stream); 
extern FILE *fopen (const char * __filename,
      const char * __modes) ; 
extern FILE *freopen (const char * __filename,
        const char * __modes,
        FILE * __stream) ; 
extern void setbuf (FILE * __stream, char * __buf) ; 
extern int setvbuf (FILE * __stream, char * __buf,
      int __modes, size_t __n) ; 
extern int fprintf (FILE * __stream,
      const char * __format, ...); 
extern int printf (const char * __format, ...); 
extern int sprintf (char * __s,
      const char * __format, ...) ; 
extern int vfprintf (FILE * __s, const char * __format,
       __gnuc_va_list __arg); 
extern int vprintf (const char * __format, __gnuc_va_list __arg); 
extern int vsprintf (char * __s, const char * __format,
       __gnuc_va_list __arg) ; 
extern int fscanf (FILE * __stream,
     const char * __format, ...) ; 
extern int scanf (const char * __format, ...) ; 
extern int sscanf (const char * __s,
     const char * __format, ...) ; 
extern int fgetc (FILE *__stream); 
extern int getc (FILE *__stream); 
extern int getchar (void); 
extern int fputc (int __c, FILE *__stream); 
extern int putc (int __c, FILE *__stream); 
extern int putchar (int __c); 
extern char *fgets (char * __s, int __n, FILE * __stream)
     ; 
extern char *gets (char *__s) ; 
extern int fputs (const char * __s, FILE * __stream); 
extern int puts (const char *__s); 
extern int ungetc (int __c, FILE *__stream); 
extern size_t fread (void * __ptr, size_t __size,
       size_t __n, FILE * __stream) ; 
extern size_t fwrite (const void * __ptr, size_t __size,
        size_t __n, FILE * __s); 
extern int fseek (FILE *__stream, long int __off, int __whence); 
extern long int ftell (FILE *__stream) ; 
extern void rewind (FILE *__stream); 
extern int fgetpos (FILE * __stream, fpos_t * __pos); 
extern int fsetpos (FILE *__stream, const fpos_t *__pos); 
extern void clearerr (FILE *__stream) ; 
extern int feof (FILE *__stream) ; 
extern int ferror (FILE *__stream) ; 
extern void perror (const char *__s); 
typedef int wchar_t; 
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
extern size_t __ctype_get_mb_cur_max (void) ; 
extern double atof (const char *__nptr)
     ; 
extern int atoi (const char *__nptr)
     ; 
extern long int atol (const char *__nptr)
     ; 
extern double strtod (const char * __nptr,
        char ** __endptr)
     ; 
extern long int strtol (const char * __nptr,
   char ** __endptr, int __base)
     ; 
extern unsigned long int strtoul (const char * __nptr,
      char ** __endptr, int __base)
     ; 
extern int rand (void) ; 
extern void srand (unsigned int __seed) ; 
extern void *malloc (size_t __size) ; 
extern void *calloc (size_t __nmemb, size_t __size)
     ; 
extern void *realloc (void *__ptr, size_t __size)
     ; 
extern void free (void *__ptr) ; 
extern void abort (void) ; 
extern int atexit (void (*__func) (void)) ; 
extern void exit (int __status) ; 
extern char *getenv (const char *__name) ; 
extern int system (const char *__command) ; 
typedef int (*__compar_fn_t) (const void *, const void *); 
extern void *bsearch (const void *__key, const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     ; 
extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) ; 
extern int abs (int __x) ; 
extern long int labs (long int __x) ; 
extern div_t div (int __numer, int __denom)
     ; 
extern ldiv_t ldiv (long int __numer, long int __denom)
     ; 
extern int mblen (const char *__s, size_t __n) ; 
extern int mbtowc (wchar_t * __pwc,
     const char * __s, size_t __n) ; 
extern int wctomb (char *__s, wchar_t __wchar) ; 
extern size_t mbstowcs (wchar_t * __pwcs,
   const char * __s, size_t __n) ; 
extern size_t wcstombs (char * __s,
   const wchar_t * __pwcs, size_t __n)
     ; 
enum {BP,BR,CE,FI,FO,HE,IND,LS,NF,PL,RM,SP,TI,UL,UNKNOWN}; 
int getcmd (buf) 
char *buf; 
{ 
char cmd[3]; ponta_de_prova (8656, 1);
    cmd[0] = buf[0]; 
    cmd[1] = buf[1]; 
    cmd[2] = '\0'; 
    if (!strcmp(cmd,"fi")) {
        ponta_de_prova (8656, 2);
        return(FI); }
    else {
        if  ( ponta_de_prova (8656, 3), (!strcmp(cmd,"nf")) ){
            ponta_de_prova (8656, 4);
            return(NF); }
        else {
            if  ( ponta_de_prova (8656, 5), (!strcmp(cmd,"br")) ){
                ponta_de_prova (8656, 6);
                return(BR); }
            else {
                if  ( ponta_de_prova (8656, 7), (!strcmp(cmd,"ls")) ){
                    ponta_de_prova (8656, 8);
                    return(LS); }
                else {
                    if  ( ponta_de_prova (8656, 9), (!strcmp(cmd,"bp")) ){
                        ponta_de_prova (8656, 10);
                        return(BP); }
                    else {
                        if  ( ponta_de_prova (8656, 11), (!strcmp(cmd,"sp")) ){
                            ponta_de_prova (8656, 12);
                            return(SP); }
                        else {
                            if  ( ponta_de_prova (8656, 13), (!strcmp(cmd,"in")) ){
                                ponta_de_prova (8656, 14);
                                return(IND); }
                            else {
                                if  ( ponta_de_prova (8656, 15), (!strcmp(cmd,"rm")) ){
                                    ponta_de_prova (8656, 16);
                                    return(RM); }
                                else {
                                    if  ( ponta_de_prova (8656, 17), (!strcmp(cmd,"ti")) ){
                                        ponta_de_prova (8656, 18);
                                        return(TI); }
                                    else {
                                        if  ( ponta_de_prova (8656, 19), (!strcmp(cmd,"ce")) ){
                                            ponta_de_prova (8656, 20);
                                            return(CE); }
                                        else {
                                            if  ( ponta_de_prova (8656, 21), (!strcmp(cmd,"ul")) ){
                                                ponta_de_prova (8656, 22);
                                                return(UL); }
                                            else {
                                                if  ( ponta_de_prova (8656, 23), (!strcmp(cmd,"he")) ){
                                                    ponta_de_prova (8656, 24);
                                                    return(HE); }
                                                else {
                                                    if  ( ponta_de_prova (8656, 25), (!strcmp(cmd,"fo")) ){
                                                        ponta_de_prova (8656, 26);
                                                        return(FO); }
                                                    else {
                                                        if  ( ponta_de_prova (8656, 27), (!strcmp(cmd,"pl")) ){
                                                            ponta_de_prova (8656, 28);
                                                            return(PL); }
                                                        else {
                                                            ponta_de_prova (8656, 29);
                                                            return(UNKNOWN); }}}}}}}}}}}}}}ponta_de_prova (8656, 30);
} 
main(argc, argv) 
int argc; 
char *argv[]; 
{ ponta_de_prova (9423, 1);
    if (argc <= 1) 
        { ponta_de_prova (9423, 2);
            printf("Erro numero de argumentos\n"); 
            exit(1); 
        } 
    ponta_de_prova (9423, 3);
    printf("%d", getcmd(argv[1])); 
} 

