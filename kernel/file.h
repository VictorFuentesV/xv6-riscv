struct file {
  enum { FD_NONE, FD_PIPE, FD_INODE, FD_DEVICE } type;
  int ref; // reference count
  char readable;
  char writable;
  struct pipe *pipe; // FD_PIPE
  struct inode *ip;  // FD_INODE and FD_DEVICE
  uint off;          // FD_INODE
  short major;       // FD_DEVICE
};

#define major(dev)  ((dev) >> 16 & 0xFFFF)
#define minor(dev)  ((dev) & 0xFFFF)
#define	mkdev(m,n)  ((uint)((m)<<16| (n)))

// in-memory copy of an inode
struct inode {
  uint dev;           // Número de dispositivo
  uint inum;          // Número de inode
  int ref;            // Contador de referencias
  struct sleeplock lock; // Protege todo lo siguiente
  int valid;          // El inode ha sido leído del disco?
  short type;         // Tipo de archivo
  short major;
  short minor;
  short nlink;
  uint size;
  uint addrs[NDIRECT+1];
  int perms;          // Permisos del archivo (nuevo campo)
};

// map major device number to device functions.
struct devsw {
  int (*read)(int, uint64, int);
  int (*write)(int, uint64, int);
};

extern struct devsw devsw[];

#define CONSOLE 1

