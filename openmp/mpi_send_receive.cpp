MPI_Send(address, count, datatype, dest, tag, comm);
// Send `count` elements of type `datatype` from the memory location `address` to the process with rank `dest` in the communication context `comm`. The message is tagged with `tag`.

MPI_Recv(address, maxcount, datatype, source, tag, comm, &status);
// Receive a message to &address of max size `maxcount` elements of type `datatype`
// from the process with rank `source` (or use `MPI_ANY_SOURCE`)
// in the communication context `comm`. The message must have the tag `tag`.
// The status of the received message is stored in the `status` object and returned.


// Both have blocking and non-blocking versions

// MPI base types:
// MPI_CHAR
// MPI_SHORT
// MPI_INT
// MPI_LONG
// ...

// MPI derived types:
// type map = {<type0, displacement0>, <type1, displacement1>, ...}
// type signature = {type0, type1, ...}
