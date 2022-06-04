# Lunching a Chameleon Instance

## Rebuild instance
```
openstack server rebuild \
--image f79b1c8a-de1c-4e0e-b18b-109e58369ac5 \
--password 1234 \
n1
```

## Floating IP
```
openstack floating ip create public --description n2
openstack floating ip list
openstack server add floating ip node-1 129.114.109.220
openstack server list
```

## Create lease
```
blazar lease-create \
  --physical-reservation min=$COUNT,max=$COUNT,resource_properties='["=", "$node_type", "storage"]' \
  --start-date "$START_DATE" \
  --end-date "$END_DATE" \
  $NAME
```

## Create Instance
```
blazar lease-list # get reservation id!!

openstack server create \
--image f79b1c8a-de1c-4e0e-b18b-109e58369ac5 \
--flavor baremetal \
--key-name chameleon-1 \
--nic net-id=1a03cf65-8fd6-4fce-94fd-bbaabe68a8e1 \
--password 1234 \
--min $COUNT \
--max $COUNT \
--hint reservation=$RESERVATION_ID \
$NAME
```
