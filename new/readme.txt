# CSE330 Operating Systems - Fall 2023
## Assignment 1 - Kernel Compilation and Installation

### Step 1: Create a new VM in VirtualBox

#### Commands Used:
- Download and install VirtualBox from the [official website](https://www.virtualbox.org/wiki/Downloads).
- Set up a new VM with the necessary specifications using the VirtualBox GUI.

#### Notes:
- Mention the specifications you chose for your VM (like number of cores, memory size, etc.).
- Mention any issues you faced and how you resolved them.

### Step 2: Install Ubuntu 22.04.3 on your new VM

#### Commands Used:
- Download Ubuntu 22.04.3 from the [Ubuntu Desktop Download](https://ubuntu.com/download/desktop) page.
- Install Ubuntu on your VM using the installation wizard in the VirtualBox GUI.




### Step 3: Compile and Install a New Kernel on Your New Ubuntu

#### Commands Used:
1. Download the kernel :wget https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/snapshot/linux-6.4.11.tar.gz

2. Uncompress the file: tar -xvf linux-6.4.11.tar.gz

3. Copy the kernel config file: cp /boot/config-$(uname -r) ./linux-6.4.11/.config

4. Install necessary dependencies:sudo apt update sudo apt install git fakeroot build-essential ncurses-dev xz-utils libssl-dev bc flex libelf-dev bison

5.Open menuconfig:make menuconfig
6. Open menuconfig: make menuconfig
7. Set the local version string in the menuconfig GUI under “General setup” -> “Local version”.
8. Check "Symmetric multi-processing support" option in the menuconfig GUI.
9. Disable conflicting security certificates:

scripts/config --disable SYSTEM_TRUSTED_KEYS
scripts/config --disable SYSTEM_REVOCATION_KEYS

10. Build the kernel: make -j4
 
11. Build the modules:

 make modules -j4
 
12. Install the new kernel modules:
 
 sudo make modules_install -j4
 
13. Install the new kernel image:
 
 sudo make install -j4

14. Configure the GRUB boot-loader:

 sudo nano /etc/default/grub
 sudo update-grub
 
15. Check the current running kernel version:
 
 uname -a
 
16.system call

#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

#define SYS_HELLO_WORLD xxx

int main()
{
    syscall(SYS_HELLO_WORLD);
    printf("helloworld\n");
    return 0;
}

exicute :dmesg | grep "Hello world"


#### Notes:
- Mention any configurations changed in the menuconfig.

- Configurations changed in the menuconfig:
  - Enabled "Symmetric multi-processing support" to allow the kernel to use multiple cores of the VM.
  - Set the hostname to a unique value to personalize my system.
- Mention any other issues you faced and how you resolved them.

- Mention any issues you faced and how you resolved them.

- Configurations changed in the menuconfig:
  - Enabled "Symmetric multi-processing support" to allow the kernel to use multiple cores of the VM.
  - Set the hostname to a unique value to personalize my system.

- Issues faced and resolutions:
  - While trying to build using the `make` command, I encountered an issue where the build process did not work as expected. To resolve this, I used the following command which specifies the directory of the kernel build system and the current directory for the module's source files:
    ```
    make -C /lib/modules/6.4.11/build/ M=$(pwd) modules
    ```
- When attempting to install gcc-13 using `sudo install gcc-13`, it did not work initially. I then tried updating the system with `sudo-  get update`, which also did not work. Finally, I resolved the issue by using the following commands to update and upgrade the system packages before installing gcc-13:
    ```
    sudo apt-get update
    sudo apt-get upgrade
    sudo apt install gcc-13
    ```
 - I encountered permission denials during the process. To overcome this, I used `sudo` and `chmod 777` to grant necessary permissions. For instance, when editing the Makefile using `gedit` did not work, I used the following command to modify the permissions and then successfully edited the file:
    ```
    chmod 777 Makefile
 
   ```
###Errors

make[1]: *** [scripts/Makefile.build:252: /home/ronald/001helloworld/main.o] Error 127
make: *** [Makefile:2038: /home/ronald/001helloworld] Error 2
make: Leaving directory '/usr/src/linux-headers-6.4.11-060411-generic' also showing this

After that i just test this also:

#include <linux/module.h>

static int __init helloworld_init(void)
{
  pr_info("hello world\n");
  return 0;
}

static void __exit helloworld_cleanup(void)
{
  pr_info("goodbye world\n");
}

module_init(helloworld_init);
module_exit(helloworld_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ME");
MODULE_DESCRIPTION("A SIMPLE HELLO WORLD");
MODULE_INFO(board, "beaglenone black EEV A5");


### Tips Followed:
- Mention any tips from the project description that you found particularly helpful.
 I	- used `sudo` and `chmod 777` liberally to bypass permission denials, given that this is a VM environment where I am expected to          	experiment and potentially make mistakes.


#### Additional Challenges and Resolutions:
- **Disk Space Issue**: During the project, I encountered a disk space issue which necessitated repartitioning my disk to allocate sufficient space for the tasks at hand. Here is how I resolved it:

  **Step 1: Boot from a Live USB/CD**
  - Booted the system from a live USB/CD to safely modify the partitions.

  **Step 2: Launch GParted**
  - Installed and launched GParted in the live environment using the following commands:
    ```sh
    sudo apt update
    sudo apt install gparted
    sudo gparted
    ```

  **Step 3: Delete /dev/sda4**
  - Selected the correct disk (/dev/sda) in GParted.
  - Located and deleted the /dev/sda4 partition to free up space.

  **Step 4: Resize /dev/sda3**
  - Utilized the unallocated space from deleting /dev/sda4 to extend the /dev/sda3 partition.
  - Resized the /dev/sda3 partition to cover the unallocated space, effectively increasing its size.

  **Step 5: Reboot**
  - Rebooted the system into the normal operating environment post the successful completion of the repartitioning process.

  **Step 6: Verify**
  - Verified that the changes were correctly applied and that the system was functioning properly post the modifications.

### Investigating "core-y" in the Linux Kernel Source Code

During the kernel compilation process, it became necessary to understand and locate the `core-y` directive within the Linux Kernel source code. This directive is fundamental in defining the core components that will be compiled into the kernel. The compilation process relies on several files and directories specified under `core-y` to build the core of the Linux kernel. Identifying and understanding the elements referenced in `core-y` provides insights into what constitutes the kernel at its most fundamental level.

#### Why did I use these commands?

1. **Listing the contents of the Linux source directory**

   ```sh
   ls /usr/src/linux-6.4.11

Searching for the “core-y” directive throughout the Linux source code : grep -r "core-y" /usr/src/linux-6.4.11
Searching for the “core-y” directive specifically in Makefiles :grep -r --include=Makefile "core-y" /usr/src/linux-6.4.11
Searching for specific paths associated with the kernel build:grep -r "kernel/certs mm fs ipc security crypto" /usr/src/linux-6.4.11



- Mention any additional resources you used.


additional resorces : https://docs.kernel.org/

### Submission
#### Screenshots:
- Mention the details of the screenshots  have taken and what they represent.

- **Outputs**: Screenshots showcasing the outputs at different stages of the kernel compilation and installation process, 	including 	the output of the `uname -a` command verifying the successful installation of the new kernel.
- **Errors**: Screenshots capturing any errors encountered during the process and how they were resolved, to provide a comprehensive view 	of the troubleshooting carried out during the project.
- **Installations**: Screenshots documenting the installation steps of various components, including the installation of necessary 	dependencies and the Ubuntu OS installation on the VM.
- **System Calls**: Screenshots demonstrating the system calls made during the project, including those made while setting configurations in `menuconfig`.
- **Steps**: Screenshots taken at different steps of the project to visually document the progression and the successful completion of 	each step, providing a visual guide to the work done.


#### Notes:
- Mention any other details you want to highlight about your submission.
 
 - **Documentation**: Alongside this README file, I have maintained detailed documentation of each step in the process, including the 	commands used and the issues faced, to provide a comprehensive view of my project journey.
- **Learning Experience**: This project was a rich learning experience, offering hands-on practice with kernel compilation and 	installation, and providing a deep understanding of the Linux boot process.
- **Collaborative Effort**: While this project was carried out independently, I ensured to actively participate in high-level discussions 	with peers to enhance my understanding and to offer assistance where I could.
- **Resource Utilization**: I leveraged a variety of resources, including lectures, TA assistance, and online materials, to successfully 	complete this project. I ensured to make the most of the resources available to me.
- **Time Management**: I managed to complete the project well within the stipulated time frame, allocating sufficient time to each step to 	ensure a thorough and detailed submission.
- **Backup and Recovery**: Throughout the project, I regularly backed up my work to prevent data loss and to facilitate easy recovery in 	case of any mishaps.
- **Ethical Compliance**: I adhered strictly to the policy against plagiarism, ensuring that all work submitted is original and that any 	references used are duly cited.


### References
- List down all the references you used to complete this project.

https://docs.kernel.org/

Name :Ronald Lin






