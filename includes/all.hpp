#pragma once

# include <algorithm>
# include <exception>
# include <cstring>
# include <cstdlib>
# include <unistd.h>
# include <cstdio>
# include <fcntl.h>
# include <poll.h>
# include <iostream>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <netdb.h>
# include <vector>

# include <csignal>
# include <map>
# include <set>
# include <deque>
# define BACKLOG 10 // nombre max de demandes de connexion

// Reset couleur
#define RES std::string("\x03")

// Couleurs de texte standard
#define WHI std::string(" \x03 ")  // Blanc (White)
#define BLA std::string("\x03,1 ")  // Noir (Black)
#define BLU std::string("\x03,2 ")  // Bleu foncé (Blue)
#define GRE std::string("\x03,3 ")  // Vert (Green)
#define RED std::string("\x03 ")  // Rouge (Red)
#define BRN std::string("\x03,5 ")  // Marron (Brown)
#define PUR std::string("\x03,6 ")  // Violet (Purple)
#define ORA std::string("\x03,7 ")  // Orange (Orange)
#define YEL std::string("\x03,8 ")  // Jaune (Yellow)
#define LGR std::string("\x03,9 ")  // Vert clair (Light Green)
#define CYA std::string("\x03,10 ")  // Cyan (Cyan)
#define LBL std::string("\x03,11 ")  // Bleu clair (Light Blue)
#define PNK std::string("\x03,12 ")  // Rose (Pink)
#define GRY std::string("\x03,13 ")  // Gris (Grey)
#define LGY std::string("\x03,14 ")  // Gris clair (Light Grey)
#define BLK std::string("\x03,15 ")  // Noir alternatif (Black)

// Couleurs en gras
#define BWHI std::string("\x02\x0300")  // Blanc en gras (Bold White)
#define BBLA std::string("\x02\x0301")  // Noir en gras (Bold Black)
#define BBLU std::string("\x02\x0302")  // Bleu foncé en gras (Bold Blue)
#define BGRE std::string("\x02\x0303")  // Vert en gras (Bold Green)
#define BRED std::string("\x02\x0304")  // Rouge en gras (Bold Red)
#define BBRN std::string("\x02\x0305")  // Marron en gras (Bold Brown)
#define BPUR std::string("\x02\x0306")  // Violet en gras (Bold Purple)
#define BORA std::string("\x02\x0307")  // Orange en gras (Bold Orange)
#define BYEL std::string("\x02\x0308")  // Jaune en gras (Bold Yellow)
#define BLGR std::string("\x02\x0309")  // Vert clair en gras (Bold Light Green)
#define BCYA std::string("\x02\x0310")  // Cyan en gras (Bold Cyan)
#define BLBL std::string("\x02\x0311")  // Bleu clair en gras (Bold Light Blue)
#define BPNK std::string("\x02\x0312")  // Rose en gras (Bold Pink)
#define BGRY std::string("\x02\x0313")  // Gris en gras (Bold Grey)
#define BLGY std::string("\x02\x0314")  // Gris clair en gras (Bold Light Grey)
#define BBLK std::string("\x02\x0315")  // Noir alternatif en gras (Bold Black)

// Couleurs de fond
#define F_WHI std::string("\x03\x0300")  // Fond blanc
#define F_BLA std::string("\x03\x0301")  // Fond noir
#define F_BLU std::string("\x03\x0302")  // Fond bleu
#define F_GRE std::string("\x03\x0303")  // Fond vert
#define F_RED std::string("\x03\x0304")  // Fond rouge
#define F_BRN std::string("\x03\x0305")  // Fond marron
#define F_PUR std::string("\x03\x0306")  // Fond violet
#define F_ORA std::string("\x03\x0307")  // Fond orange
#define F_YEL std::string("\x03\x0308")  // Fond jaune
#define F_LGR std::string("\x03\x0309")  // Fond vert clair
#define F_CYA std::string("\x03\x0310")  // Fond cyan
#define F_LBL std::string("\x03\x0311")  // Fond bleu clair
#define F_PNK std::string("\x03\x0312")  // Fond rose
#define F_GRY std::string("\x03\x0313")  // Fond gris
#define F_LGY std::string("\x03\x0314")  // Fond gris clair
#define F_BLK std::string("\x03\x0315")  // Fond noir alternatif


class Client;
class Channel;
class Server;

# include "Server.hpp"
# include "Channel.hpp"
# include "Client.hpp"