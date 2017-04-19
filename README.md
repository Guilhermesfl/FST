# FST
IP Lookup Algorithm using Fixed Stride Size Multibit Trie structure and coprocessor Intel® Xeon Phi 

## Abstract
Since the development of CIDR in 1993, IPv4 routing is based in routing lookup tables
(Longest Matching Prefix)to extract the next hop, further being a memory-intensive algorithm. 
Due to the huge grow of routing tables, IP lookup became the performance bottleneck in internet routers.
Seeking to achieve better perfomances in the IP lookup process, the solution founded in software 
is to use GPGPU and new algorithms to extract the maximum of the inner parallelism of the IP lookup.
