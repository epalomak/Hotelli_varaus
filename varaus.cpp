/****************************************************/
/* @ Author: Eino Palomaki                          */
/* @ Create Time: 2022-11-21 13:20:27               */
/* @ Modified by: Eino Palomaki                     */
/* @ Modified time: 2022-12-12 11:48:16             */
/****************************************************/

#include"header.h"

// Kysyy käyttäjältä öiden määrän, huonetyypin, valitaanko huone itse/arvotaanko se, nimen ja arpoo varausnumeron.
// Lopuksi ohjelma vielä tulostaa varauksesta kuitin. Aliohjelma ottaa parametreina vapaana olevat huoneet, huone määrän ja hotellihuone 2D - structin.
void		huoneen_varaus(int &vapaana, int h_maara, Hotelli* hotellihuoneet)
{
	int valinta, hkoko, hnro, p_maara, i = 0;
	bool virhe;


	cout << "\nHotellissa on vapaana " << vapaana << " huonetta\n";
	// näyttää käyttäjälle huoneiden hinnat
	hinnat();

	cout << "kuinka monta yötä haluat viipyä? ";
	p_maara = tarkistus(2);

	cout << "\nVarataanko yhden vai kahden hengen huoneen?(valitse 1 tai 2): ";
	hkoko = tarkistus(3);

	cout << "\nHaluatko itse(1) valita huoneen vai arvotaanko(2) se (valitse 1 tai 2): ";
	valinta = tarkistus(3);
	
	// 1 = käyttäjä haluaa itse valita huoneen.
	if (valinta == 1)
	{
		// tarkistetaan haluttu huone koko
		if (hkoko == 1)
		{
			// h_maara:sta vähennetään 40 enne jakoa(jaolla saada puolet huoneista), koska huonee numerot alkaa neljästäkymmenestä
			cout << "Valitse huone väliltä 40 - " << (h_maara - 40) / 2 + 40 << " : ";
			// kysytään käyttäjältä uutta syötettä niin kauan kunnes syöte on oikein ja syötetty huone on vapaa 
			do
			{
				virhe = false;
				cin >> hnro;
				if (cin.fail() || (hnro > (h_maara - 40) / 2 + 40 || hnro < 40))
				{
					cout << "Huonetta ei ole/se on 2hh huone.\nValitse väliltä 40 - " << (h_maara - 40) / 2 + 40 << " : ";
					virhe = true;
					cin.clear();
					cin.ignore(80, '\n');
				}
				// tarkistetaan että syöte on ollut oikein (siksi virheen pitää olla false) ja sen jälkeen tarkistetaan onko huone varattu
				if (virhe == false && onko_vapaa(hotellihuoneet, hnro))
				{
					cout << "Huone on jo varattu valitse toinen huone!\n";
					i++; // lasketaan muuttujaan kuinka monta huonetta on varattu
					virhe = true;
				}
				// tarkistetaan onko kaikki yhden hengen huoneet varattu ja jos on kertoo käyttäjälle ja palauttaa käyttäjän valikkoon
				if (i == (h_maara - 40 / 2))
				{
					cout << "Valitettavasti kaikki yhden hengen huoneet ovat varattuja. Kahden hengen huoneita on vielä vapaana!\n";
					return ;
				}
			} while (virhe);
		}
		// jos haluttu huone koko ei ollut 1 niin sen pitää olla 2 siksi tässä vain else.
		else
		{
			cout << "Valitse huone väliltä " << (h_maara - 40) / 2 + 40 << " - " << h_maara << " : ";
			do
			{
				virhe = false;
				cin >> hnro;
				if (cin.fail() || (hnro > h_maara || hnro < (h_maara - 40) / 2 + 40))
				{
					cout << "Huonetta ei ole/se on 1hh huone.\nValitse huone väliltä " << (h_maara - 40) / 2 + 40 << " - " << h_maara << " : ";
					virhe = true;
					cin.clear();
					cin.ignore(80, '\n');
				}
				if (virhe == false && onko_vapaa(hotellihuoneet, hnro))
				{
					cout << "Oho huone on jo varattu valitse toinen huone!\n";
					i++;
					virhe = true;
				}
				if (i == (h_maara - 40 / 2))
				{
					cout << "Valitettavasti kaikki kahden hengen huoneet ovat varattuja. Yhden hengen huoneita on vielä vapaana!\n";
					return ;
				}
			} while (virhe);
		}
	}
	// jos valinta = 2 niin huone arvotaan
	else
	{
		//aliohjelma arvonta palauttaa NULL jos vapaita huoneita haluttuun huonetyyppiin ei löytynyt siksi if() ja palauttaa käyttäjän valikkoon
		if (!(hnro = arvonta(hkoko, h_maara, hotellihuoneet)))
			return ;
	}

	//asetetaan kaikki saadut arvot structiin huonenumeron määrämällle paikalle
	hotellihuoneet[hnro].p_maara = p_maara;
	hotellihuoneet[hnro].hnro = hnro;
	hotellihuoneet[hnro].hkoko = hkoko;
	hotellihuoneet[hnro].varattu = true;
	// kysytään vielä varaajan nimi
	cout << "Varajaan nimi: ";
	cin.ignore();
	getline(cin, hotellihuoneet[hnro].nimi); 
	// asetetaan huoneelle hinta, aliohjelma arpoo tuleeko kokonaishintaan alennus
	hotellihuoneet[hnro].hinta = huoneen_hinta(hkoko, p_maara);
	// arvotaan varausnumero
	hotellihuoneet[hnro].varausnro = rand_nro(10000, 99999);
	// tulostetaan varauksen kaikki tiedot käyttäjälle
	tulosta_kuitti(hotellihuoneet[hnro]);
	// vähennetään vapaista huoneista yksic
	vapaana--;

}

// Peruu halutun varauksen, kun varaus on löydetty varausnumerolla. Ottaa parametreina 2D-structin, huone määrän ja vapaana olevien huoneiden määrän
void	varauksen_peruutus(Hotelli* hotellihuoneet, int h_maara, int &vapaana)
{
	int varausnro,valinta, i, oikeavarausnro = 0;
	bool virhe;

	//goto komennon paikka johon kutsuttaessa palataan
	varaus_numeron_syotto: 
	cout << "Syötä sen varauksen varausnumero, jonka haluat perua.(Jos et haluakkaan perua varausta paina 1): ";

	//tarkistetaan syöte ja annetaan mahdollisuus poistua jos peruutusta ei haluta tehdä
	do
	{
		virhe = false;
		cin >> varausnro;
		if (varausnro == 1)
			return;
		if (cin.fail() || (varausnro > 99999 || varausnro < 10000))
		{
			cout << "\nVirhe! Varausnumero on välillä 10000 - 99999 tai syötä 1 poistuaksesi.\n\n";
			virhe = true;
			cin.clear();
			cin.ignore(80, '\n');
		}
	} while (virhe);

	i = 39;
	// tarkistetaan löytyykö varausta i = 39, koska while loopin alussa lisään i:n arvoa yhdellä ja huonenumerot alkaa vasta 40 joten paikkoja 0 - 39 ei tarvitse tarkistaa
	while (i++ <= h_maara)
	{
		if (hotellihuoneet[i].varausnro == varausnro)
		{
			oikeavarausnro = 1;
			break;
		}
	}
	// jos huonetta ei löytynyt palataan goto komennolla ohjelman alkuun 
	if (oikeavarausnro == 0)
	{
		cout << "Varausnumerolla: " << varausnro << " ei löytynyt yhtään varausta!\nTarkista kirjoitiko varausnumeron oikein.\n";
		goto varaus_numeron_syotto;
	}
	//tulostetaan löydetty varaus ja varmistetaan vielä haluaako käyttäjä varmasti perua
	tulosta_kuitti(hotellihuoneet[i]);
	cout << "Haluatko varmasti peruuttaa varauksen?(vastaa 1(kyllä) tai 2(ei)): ";
	valinta = tarkistus(3);
	// käyttäjän halutessa edelleen perua varaus poistetaan nollaamalla structin paikan tiedot.
	if (valinta == 1)
	{
		hotellihuoneet[i] = poista_varaus(hotellihuoneet[i]);
		vapaana++;
	}
	// jos varausta ei tehdä poistutaan ohjelmasta
	else
		return ;
}

// aliohjelmassa voit tarkastella varauksiasi joko etsimällä niitä nimellä(näin löydät kaikki nimellä tehdyt varaukset) tai varausnumerolla.
void	varauksen_tarkastelu(Hotelli *hotellihuoneet, int h_maara)
{
	int valinta, varausnro, osuma = 0, i = 39;
	bool virhe;
	string nimi;

	cout << "Valitse haetko varausta nimellä(1) vai varausnumerolla(2): ";
	valinta = tarkistus(3);

	if (valinta == 1)
	{
		// goto komennon paluu paikka, jos nimellä ei löydy varausta
		nimen_syotto:
		cout << "Varajaan nimi: ";
		cin.ignore();
		getline(cin, nimi);
		// tarkistetaan std kirjaston compare functiolla täsmääkö syötetty nimi yhteenkään varaukseen, ja tulostetaan kaikki nimellä löydetyt varaukset 
		while(i++ < h_maara)
		{
			if (hotellihuoneet[i].nimi.compare(nimi) == 0)
			{
				osuma = 1;
				tulosta_kuitti(hotellihuoneet[i]);
			}		
		}
	}
	// jos nimellä ei löydy varauksia paltaan goto komennolla sille osoitettuun paikkaan. Tässä kohtaa nimen_syotto
	if (osuma == 0)
	{
		cout << "Nimellä: " << nimi << " ei löytynyt yhtään varausta! \nTarkista kirjoitiko nimen oikein.\n";
		goto nimen_syotto;
	}
	else if (valinta == 2)
	{
		// goto komennon paluu paikka, jos varausnumerolla ei löydy varausta
		varaus_numeron_syotto:
		cout << "Syötä varausnumero: ";
		//tarkistetaan että syöte on oikein
		do
		{
			virhe = false;
			cin >> varausnro;
			if (cin.fail() || (varausnro > 99999 || varausnro < 10000))
			{
				cout << "\nVirhe! Varausnumero välillä 10000 - 99999.\n\n";
				virhe = true;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (virhe);
		// Tarkistetaan löytyikö varausnumerolla yhtään varausta
		while (i++ <= h_maara)
		{
			if (hotellihuoneet[i].varausnro == varausnro)
			{
				osuma = 1;
				break;
			}
		}
		// jos varauksia ei löytyny palataan goto komennolla sille nimettyyn paikkaan. Tässä kohtaa varaus_numeron_syotto
		if (osuma == 0)
		{
			cout << "Varausnumerolla: " << varausnro << " ei löytynyt yhtään varausta! \nTarkista kirjoitiko varausnumeron oikein.\n";
			goto varaus_numeron_syotto;
		}
		// mikäli varaus löydettiin tulostetaan se käyttäjälle
		tulosta_kuitti(hotellihuoneet[i]);
	}

}
