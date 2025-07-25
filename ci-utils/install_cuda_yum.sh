#!/bin/bash
# Usage: $bash install_cuda_yum.sh <VERSION>

version=$1

if [ $version -eq 11 ]; then
    yum-config-manager --add-repo https://developer.download.nvidia.com/compute/cuda/repos/rhel7/x86_64/cuda-rhel7.repo
    yum clean all
    yum -y module install nvidia-driver:latest-dkms
    echo "Installing cuda toolkit 11"
    yum -y install cuda-11-8
    echo 'export PATH=/usr/local/cuda-11.8/bin:$PATH' >> ~/.bashrc
    echo 'export LD_LIBRARY_PATH=/usr/local/cuda-11.8/lib64:$LD_LIBRARY_PATH' >> ~/.bashrc
    source ~/.bashrc
elif [ $version -eq 12 ]; then
    dnf config-manager --add-repo https://developer.download.nvidia.com/compute/cuda/repos/rhel8/x86_64/cuda-rhel8.repo
    dnf clean all
    dnf -y module install nvidia-driver:latest-dkms
    dnf -y install cuda-toolkit-12-8
    echo "Installing cuda toolkit 12"
    echo 'export PATH=/usr/local/cuda-12.8/bin:$PATH' >> ~/.bashrc
    echo 'export LD_LIBRARY_PATH=/usr/local/cuda-12.8/lib64:$LD_LIBRARY_PATH' >> ~/.bashrc
    source ~/.bashrc
else
    echo "Invalid version. Please provide either 11 or 12."
    exit 1
fi

ls -al /usr/local
export PATH=$PATH:/usr/local/cuda/bin
nvcc --version