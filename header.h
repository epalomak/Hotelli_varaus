 /****************************************************/
 /* @ Author: Eino Palomaki                          */
 /* @ Create Time: 2022-12-12 13:40:44               */
 /* @ Modified by: Eino Palomaki                     */
 /* @ Modified time: 2022-12-14 12:29:40             */
 /****************************************************/

#ifndef HEADER_H
#define HEADER_H

#include<iostream>
#include<iomanip>
#include<string>
#include<cmath>
#include<clocale>
#include<time.h>
#include<random>
#include<windows.h>

using namespace std;

//m‰‰ritet‰‰n vakioina menussa ja kuitissa k‰ytetty v‰ri ja sille resetointi
const		string color = "\033[1;33m", reset = "\033[0m";
//vakiot hinnalle, alennukselle ja max huonenumerolle
const		double alennus[3] = {1, 0.90, 0.80 };
const		double h1_hinta = 100, h2_hinta = 150;
const		int	max_huoneet = 301;

//struct joka pit‰‰ sis‰ll‰‰n kaiken olennaisen tiedon
struct		Hotelli
{
			string nimi;
			int varausnro = 0;
			int hkoko = 0;
			int p_maara = 0;
			double hinta = 0;
			int hnro = 0;
			bool varattu = false;
};

// kaikkien aliohjelmien prototyypit
void		varauksen_tarkastelu(Hotelli*, int);
void		varauksen_peruutus(Hotelli*, int, int&);
void		huoneen_varaus(int&, int, Hotelli*);
int			rand_nro(int, int);
void		tulosta_kuitti(Hotelli);
void		hinnat();
int 		tarkistus(int);
bool		onko_vapaa(Hotelli*, int);
int			arvonta(int, int, Hotelli*);
double		huoneen_hinta(int, int);
Hotelli		poista_varaus(Hotelli);

#endif
