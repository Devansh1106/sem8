## Comparison based on varying threads
This is for 1 GPU

M = N =   16384
Multi-GPU Time: 183.829376 ms
Verification: y[0](gpu) = 4090.139648
threads_per_block=64

M = N =   16384
Multi-GPU Time: 113.764061 ms
Verification: y[0](gpu) = 4090.139648
threads_per_block=128

M = N =   16384
Multi-GPU Time: 114.884605 ms
Verification: y[0](gpu) = 4090.139648
threads_per_block=256

M = N =   16384
Multi-GPU Time: 117.250015 ms
Verification: y[0](gpu) = 4090.139648
theards_per_block=512

M = N =   16384
Multi-GPU Time: 123.646500 ms
Verification: y[0](gpu) = 4090.139648
threads_per_block=1024

---

This is for 2 GPUs
M = N =   16384
Multi-GPU Time: 273.169250 ms
Verification: y[0](gpu) = 4090.139648
threads_per_block = 1024

M = N =   16384
Multi-GPU Time: 257.326996 ms
Verification: y[0](gpu) = 4090.139648
threads_per_block = 512

M = N =   16384
Multi-GPU Time: 260.723541 ms
Verification: y[0](gpu) = 4090.139648
threads_per_block = 256

M = N =   16384
Multi-GPU Time: 259.719177 ms
Verification: y[0](gpu) = 4090.139648
threads_per_block = 128

M = N =   16384
Multi-GPU Time: 255.764191 ms
Verification: y[0](gpu) = 4090.139648
threads_per_block = 64

---
## Comparison based on varying GPUs vs CPU

Timings for numGPUs = 1
M = N = 8192
Serial Time:    212.090000 ms
Multi-GPU Time: 69.369347 ms
Verification: y[0](gpu) = 2064.640137 and (cpu) 2064.640137

M = N =   16384
Serial Time:    817.151000 ms
Multi-GPU Time: 258.717743 ms
Verification: y[0](gpu) = 4090.139648 and (cpu) 4090.139648

M = N =   32768
Serial Time:    3234.022000 ms
Multi-GPU Time: 1010.047791 ms
Verification: y[0](gpu) = 8177.334961 and (cpu) 8177.334961

---

Now is the timing for 2 GPUs:
M = N =   32768
Serial Time:    3293.031000 ms
Multi-GPU Time: 1157.799316 ms
Verification: y[0](gpu) = 8177.334961 and (cpu) 8177.334961

M = N =   16384
Serial Time:    828.926000 ms
Multi-GPU Time: 419.553314 ms
Verification: y[0](gpu) = 4090.139648 and (cpu) 4090.139648

M = N =   8192
Serial Time:    210.971000 ms
Multi-GPU Time: 238.031097 ms
Verification: y[0](gpu) = 2064.640137 and (cpu) 2064.640137