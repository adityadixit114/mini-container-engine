# Mini Container Engine from Scratch

A lightweight container isolation and sandboxing engine written in C/C++ leveraging Linux kernel primitives directly without relying on Docker or runc.

## Technical Mechanisms
- **Linux Namespaces**: PID (process isolation), MNT (mount isolation), NET (network namespace), UTS (hostname isolation).
- **Cgroups v2**: Resource control subsystem restricting maximum memory footprint and CPU quota.
- **Seccomp-BPF**: Kernel system call filtering to restrict malicious or dangerous syscall execution.
- **Layered Rootfs**: Pivot root and OverlayFS-based isolated filesystem structure.

## Compilation & Run
```bash
# Clone
git clone https://github.com/adityadixit114/mini-container-engine.git
cd mini-container-engine

# Build with GCC on Linux
make
sudo ./bin/mini-container run /bin/sh
```
