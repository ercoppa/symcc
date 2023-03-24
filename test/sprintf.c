// This file is part of SymCC.
//
// SymCC is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// SymCC is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// SymCC. If not, see <https://www.gnu.org/licenses/>.

// RUN: %symcc %s -o %t
// RUN: echo -ne "\x00" | %t 2>&1 | %filecheck %s
//
// Check that sprintf clears the symbolic memory of the output buffer

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char c[8];

  ssize_t nbytes = read(STDIN_FILENO, c, 1);
  if (nbytes != 1)
    return 1;

  sprintf(c, "0%d", 1);

  // SIMPLE-NOT: Trying to solve
  // QSYM-NOT: SMT
  if (c[0])
    fprintf(stderr, "Concrete: %s\n", c);
  else
    fprintf(stderr, "Symbolic: %s\n", c);
  return 0;
}