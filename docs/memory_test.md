# Memory Leak Testing

## Summary
- On startup the memory usage is 5M
- On first API Get call, it expands to 11M
- On a different call on different thread (Httpie) it expands to 12M
- Use Leaks tool to verify if memory allocation 

Use Leaks tool on macOS to verify

```
leaks CppUserAPI
```

You will get a report like the following:

```
Process 48119 is not debuggable. Due to security restrictions, leaks can only show or save contents of readonly memory of restricted processes.

Process:         CppUserAPI [48119]
Path:            /CppUserAPI
Load Address:    0x104210000
Identifier:      CppUserAPI
Version:         0
Code Type:       ARM64
Platform:        macOS
Parent Process:  fish [17317]
Target Type:     live task

Date/Time:       2026-03-04 19:24:54.562 +1100
Launch Time:     2026-03-04 19:13:25.757 +1100
OS Version:      macOS 15.7.4 (24G517)
Report Version:  7
Analysis Tool:   /usr/bin/leaks

Physical footprint:         5313K
Physical footprint (peak):  5313K
Idle exit:                  untracked
----

leaks Report Version: 4.0
Process 48119: 10109 nodes malloced for 827 KB
Process 48119: 0 leaks for 0 total leaked bytes.
```

The import line is this:

```
Process 48119: 0 leaks for 0 total leaked bytes.
```
