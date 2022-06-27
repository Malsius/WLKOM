# WLKOM : Wild Linux Kernel Object Module

Création d'un kernel object qui utilise un fichier device

Pour make le module :
- make

Pour load le module :
- Alphabet par défaut : make load
- Alphabet personnalisé : sudo insmod ./wlkom.ko alphabet="42test."

Pour créer la device dans /dev :
- Aller voir quelle sous quel major a été enregistrée le device soit avec cat /proc/devices soit en allant voir les log kernel avec dmesg -Hw
- Faire la commande sudo mknod /dev/wlkom c major 0

Pour tester ce que return la device :
- cat /dev/wlkom

Pour clean le tout :
- make unload rmdev clean
