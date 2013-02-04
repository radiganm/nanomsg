/*
    Copyright (c) 2012 250bpm s.r.o.

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom
    the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "../src/nn.h"
#include "../src/pair.h"

#include "../src/utils/err.c"
#include "../src/utils/thread.c"
#include "../src/utils/sleep.c"

void worker (void *arg)
{
    int rc;
    int s;
    char buf [3];

    s = nn_socket (AF_SP, NN_PAIR);
    errno_assert (s != -1);
    rc = nn_recv (s, buf, sizeof (buf), 0);
    nn_assert (rc == -1 && nn_errno () == ETERM);
    rc = nn_close (s);
    errno_assert (rc == 0);
}

int main ()
{
    int rc;
    int s;
    struct nn_thread thread;

    /*  Close the socket with no associated endpoints. */
    rc = nn_init ();
    errno_assert (rc == 0);
    s = nn_socket (AF_SP, NN_PAIR);
    errno_assert (s != -1);
    rc = nn_close (s);
    errno_assert (rc == 0);
    rc = nn_term ();
    errno_assert (rc == 0);

    /*  Test nn_term() before nn_close(). */
    rc = nn_init ();
    errno_assert (rc == 0);
    nn_thread_init (&thread, worker, NULL);
    nn_sleep (10);
    rc = nn_term ();
    errno_assert (rc == 0);
    nn_thread_term (&thread);

    return 0;
}
