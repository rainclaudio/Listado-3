#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <features.h>    /* for the glibc version number */
#if __GLIBC__ >= 2 && __GLIBC_MINOR >= 1
#include <netpacket/packet.h>
#include <net/ethernet.h>     /* the L2 protocols */
#else
#include <asm/types.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>   /* The L2 protocols */
#endif


#include <stdlib.h>
#include <string.h>
int getsocket(char * interfaz){
	unsigned char bufer[4000];//bufer para recibir unidad de datos
	struct sockaddr_ll sa;    //para manejar el socket
	struct	ifreq ifr;        //para manejar una interfaz
	struct ethhdr *eth;       //para manejar el bufer como ethernet
	struct ip *ip;            //para manejar el bufer (datos ethernet) como protocolo ip
	struct packet_mreq mr;
	int packet_socket,lar,b,eth_index;

	memset(&sa, 0, sizeof(struct sockaddr_ll));//limpia
	packet_socket = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));//abre el socket a nivel 2
	//packet_socket = socket(PF_PACKET, SOCK_DGRAM, htons(ETH_P_ALL));//solo el campo de datos
	printf("socket: %d\n",packet_socket);

	memset(&ifr,0,sizeof(struct ifreq));
	strncpy(ifr.ifr_name, interfaz, sizeof(ifr.ifr_name));
	eth_index = ioctl(packet_socket, SIOCGIFINDEX, &ifr);//obtiene el indice de la interfaz (eth0,eth1, otros)
	printf("index %d <--> %s\n", ifr.ifr_ifindex, ifr.ifr_name);

	sa.sll_protocol = htons(ETH_P_ALL);//recibe todos a esta y broadcast
	sa.sll_family=AF_PACKET;
	sa.sll_ifindex=ifr.ifr_ifindex;
	b=bind(packet_socket, (struct sockaddr *)&sa, sizeof(struct sockaddr_ll));//para elegir interfaz
	printf("bind: %d\n",b);

  // pone el dispositivo en modo promiscuo.
	memset(&mr, 0, sizeof(mr));
	mr.mr_ifindex = ifr.ifr_ifindex;
	mr.mr_type = PACKET_MR_PROMISC;
	if (setsockopt(packet_socket, SOL_PACKET, PACKET_ADD_MEMBERSHIP, (void *)&mr, (socklen_t)sizeof(mr)) == -1) {
		printf("No se puede poner interfaz en modo promiscuo %s\n");
    		close(packet_socket);
    		packet_socket = -1;
    		exit(-1);
  	}


return packet_socket;

}


main(int argc,char *argv[]){
        unsigned char bufer[4000];
        int lar, ps;
        ps=getsocket(argv[1]);
	while(1){
		lar=recv(ps, (void *)bufer, sizeof(bufer), 0);
		printf("largo: %d:\t",lar);
		printf("%02x:%02x:%02x:%02x:%02x:%02x\t",bufer[0],bufer[1],bufer[2],bufer[3],bufer[4],bufer[5]);
		printf("%02x:%02x:%02x:%02x:%02x:%02x ",bufer[6],bufer[7],bufer[8],bufer[9],bufer[10],bufer[11]);
		printf("\tprotocolo: %02x%02x ",bufer[12],bufer[13]);
	printf("\n");
	}
}
