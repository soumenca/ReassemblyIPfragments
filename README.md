# Reassembly of IP fragments

The purpose of this assignment is to understand reassembly of IP fragments.

The program should accept the name of an input file as a command line argument. This file will have the information regarding fragments. You need to parse the contents of this file and using the information read,need to reassemble the fragments. Use fgets and sscanf/strtok to parse the fields of a record.

The format of the file is as given below: There is a space between fields in the record.
"IPsourceaddr" "ID" "fragOffset" "MF" "Length"

The IP source address is given in dotted decimal notation. Use the system call inet_addr to convert it into an unsigned long and store it in your data structure as an unsigned long. Remember that string operations such as comparison are much costlier than integer comparisons. Hence, store the IP address as an unsigned long.

NOTE: See the manual page of inet_addr to understand how to invoke it and what include files to use and
the input and output parameters.

The output of the program should be the following:
For every "IP source addr, ID" combination read, print whether the fragments given form a complete datagram. If so, print the Source IP address in dotted decimal notation using inet_ntoa, ID and total length of the datagram. If not, print the Source IP address and ID and the error encountered while reassembling such as, "Duplicate Fragment", "Missing Fragment", "Mismatch in length" etc..

Given below is sample data:
172.16.88.12 1 0 0 64
172.16.88.12 1 0 1 1480
172.16.88.12 1 0 0 64
202.41.85.117 1 0 0 64
202.41.85.117 1 0 0 1480
