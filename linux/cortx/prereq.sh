disk="/dev/sda" # device name
fs_mount_path="/opt" # mounting path 


function prepCortxDeployment()
{

    if [[ $(findmnt -m $fs_mount_path) ]];then
        echo "$fs_mount_path already mounted..."
    else
        mkdir -p $fs_mount_path
        echo y | mkfs.ext4 $disk
        mount -t ext4 $disk $fs_mount_path
    fi

    # Prep for Rancher Local Path Provisioner deployment
    echo "Create folder '$fs_mount_path/local-path-provisioner'"
    mkdir -p $fs_mount_path/local-path-provisioner
    count=0
    while true; do
        if [[ -d $fs_mount_path/local-path-provisioner || $count -gt 5 ]]; then
            break
        else
            echo "Create folder '$fs_mount_path/local-path-provisioner' failed. Retry..."
            mkdir -p $fs_mount_path/local-path-provisioner
        fi
        count=$((count+1))
        sleep 1s
    done
}

function increaseResources()
{
    sysctl -w vm.max_map_count=30000000;
}


function prepOpenLdapDeployment()
{
    mkdir -p /etc/3rd-party/openldap
    mkdir -p /var/data/3rd-party
    mkdir -p /var/log/3rd-party
}

function installHelm()
{
    curl https://raw.githubusercontent.com/helm/helm/main/scripts/get-helm-3 | bash
}

function cleanupFolders()
{
    rm -rf /etc/3rd-party/openldap /var/data/3rd-party/*
    rm -rf $fs_mount_path/local-path-provisioner/*
}


cleanupFolders
increaseResources
prepCortxDeployment
prepOpenLdapDeployment



