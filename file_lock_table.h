// Copyright (c) 2016, Robert Escriva
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright notice,
//       this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of this project nor the names of its contributors may
//       be used to endorse or promote products derived from this software
//       without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef e_file_lock_table_h_
#define e_file_lock_table_h_

// POSIX
#include <sys/types.h>

// STL
#include <set>

// po6
#include <po6/threads/mutex.h>

namespace e
{

class file_lock_table
{
    public:
        static file_lock_table* the_one_and_only();

    public:
        file_lock_table();
        ~file_lock_table() throw ();

    public:
        bool acquire(dev_t dev, ino_t ino);
        void release(dev_t dev, ino_t ino);

    private:
        typedef std::pair<dev_t, ino_t> file_t;
        typedef std::set<file_t> file_map_t;
        po6::threads::mutex m_mtx;
        file_map_t m_files;

    private:
        file_lock_table(const file_lock_table&);
        file_lock_table& operator = (const file_lock_table&);
};

} // namespace e

#endif // e_file_lock_table_h_
