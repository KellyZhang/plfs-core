#ifndef __FLATFILE_H_
#define __FLATFILE_H_

#include "plfs_private.h"
#include "LogicalFS.h"
#include "LogicalFD.h"
#include <string>

class Flat_fd : public Plfs_fd {
 public:
    Flat_fd() {refs = 0; backend_fd = -1;};
    ~Flat_fd();
    // These are operations operating on an open file.
    int open(const char *filename, int flags, pid_t pid,
             mode_t mode, Plfs_open_opt *open_opt);
    int close(pid_t, uid_t, int flags, Plfs_close_opt *);
    ssize_t read(char *buf, size_t size, off_t offset);
    ssize_t write(const char *buf, size_t size, off_t offset, pid_t pid);
    int sync(pid_t pid);
    int trunc(const char *path, off_t offset);
    int getattr(const char *path, struct stat *stbuf, int sz_only);
    int query(size_t *writers, size_t *readers, size_t *bytes_written, bool *reopen);
    bool is_good();
    int my_type_id() {return FLAT_FILE;};
 private:
    std::string backend_pathname;
    int backend_fd;
};

// These are file-system level operations:

class FlatFileSystem : public LogicalFileSystem {
 public:

    // here are the methods for creating an instatiated object
    int open(Plfs_fd **pfd,const char *logical,int flags,pid_t pid,
             mode_t mode, Plfs_open_opt *open_opt);

    // here are a bunch of methods for operating on one
    // these should be static but there aren't static virtual methods
    int getattr(const char *logical, struct stat *stbuf,int sz_only);
    int trunc(const char *logical, off_t offset, int open_file);
    int chown(const char *logical, uid_t u, gid_t g);
    int chmod(const char *logical, mode_t mode);
    int getmode(const char *logical, mode_t *mode);
    int access(const char *logical, int mask);
    int rename(const char *logical, const char *to);
    int link(const char *logical, const char *to);
    int utime(const char *logical, struct utimbuf *ut);
    int unlink(const char *logical);
    int create(const char *logical, mode_t, int flags, pid_t pid);
    int mkdir(const char *path, mode_t);
    int readdir(const char *path, void *buf);
    int readlink(const char *path, char *buf, size_t bufsize);
    int rmdir(const char *path);
    int symlink(const char *path, const char *to);
    int statvfs(const char *path, struct statvfs *stbuf);
};

extern FlatFileSystem flatfs;

#endif
