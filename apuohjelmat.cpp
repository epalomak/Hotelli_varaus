/****************************************************/
/* @ Author: Eino Palomaki                          */
/* @ Create Time: 2022-12-12 11:06:05               */
/* @ Modified by: Eino Palomaki                     */
/* @ Modified time: 2022-12-12 11:41:24             */
/****************************************************/

#include"header.h"

// Arpoo satunnaisen numeron annetulla numero välillä
int		rand_nro(int minimi, int maximi)
{
	//haetaan satunnaisnumero kone
	static random_device rd;
	//asetetaan rd:hen mitä satunnaisnumero konetta käytetään
	static mt19937 rng(rd()); 
	// asetetaan minimi ja maximi ja mitä tyyppiä satunnaisnumero generaattorista halutaan
	uniform_int_distribution<int> dis(minimi, maximi);

	return(dis(rng));
}

// tulostaa kaikki sille syötetyn structin tiedot käyttän nähtäväksi
void	tulosta_kuitti(Hotelli hotellihuoneet)
{	
	cout << color << "________________________________________\n" << reset;
	cout << "	Varaaja: " << hotellihuoneet.nimi << endl;
	cout << "	Varausnumero: " << hotellihuoneet.varausnro  << endl;
	cout << "	Huoneen koko: " << hotellihuoneet.hkoko << " hengen huone" << endl;
	cout << "	Huone numero: " << hotellihuoneet.hnro << endl;
	cout << "	Öiden maara: " << hotellihuoneet.p_maara << endl;
	cout  << "	Kokonaishinta: " << hotellihuoneet.hinta << " euroa" << endl;
	cout << color << "________________________________________\n\n" << reset;

}

// näyttää käyttäjälle huoneiden hinnat
void hinnat()
{
	cout << "\nYhden hengen huoneen hinta on " << h1_hinta << " euroa\n";
	cout << "Kahden hengen huoneen hinta on " << h2_hinta << " euroa\n\n";

}

// tulostaa käyttäjälle menun
void	menu()
{
	cout << color << " ________________________________________________________\n";
	cout << "|					  		 |\n";
	cout << "|	" << reset << "    TERVETULOA HOTELLIN VARAUKSEEN!" << color << "		 |\n";
	cout << "|					  		 |\n";
	cout << "| " << reset << "Valitse toiminto numerolla (1-4)." << color << "			 |\n";
	cout << "|					  		 |\n";
	cout << "| " << reset << "1. Tee uusi varaus." << color << "	 	 		 	 |\n";
	cout << "|					  		 |\n";
	cout << "| " << reset << "2. Peru varausta." << color << " 					 |\n";
	cout << "|					  		 |\n";
	cout << "| " << reset << "3. Tarkastele varauksiasi." << color << "	 			 |\n";
	cout << "|					  		 |\n";
	cout << "| " << reset << "4. Lopeta ohjelma." << color << "	 				 |\n";
	cout << "|					  		 |\n";
	cout << "|________________________________________________________|\n\n" << reset;
}

// tarkistaa syötteen ja ottaa parametrina mitä syöte tyyppiä tarkastetaan, lisäsin tähän vain ne syötteen tarkistukset joita käytetään usein ja 
// niitä tarkistaessa ei tarvita monia eri tarkistuksia. Paluttaa tarkistetun syötteen
int tarkistus(int mita_tarkistetaan)
{
	int palautus;
	bool virhe;

	if (mita_tarkistetaan == 1)
	{
		do
		{
			virhe = false;
			menu();
			cin >> palautus;
			if (cin.fail() || (palautus > 4 || palautus < 0))
			{
				cout << "\nVirhe! Muista valita numerolla 1 - 4.\n\n";
				virhe = true;
				cin.clear();
				cin.ignore(80, '\n');
			}

		} while (virhe);
	}
	if (mita_tarkistetaan == 2)
	{
		do
		{
			virhe = false;
			cin >> palautus;
			if (cin.fail() || (palautus > 365 || palautus < 1))
			{
				cout << "virhe! Valitse enemmän kuin 0 tai vähemmän kuin 365\n";
				virhe = true;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (virhe);
	}
	if (mita_tarkistetaan == 3)
	{
		do
		{
			virhe = false;
			cin >> palautus;
			if (cin.fail() || (palautus > 2 || palautus < 1))
			{
				cout << "Oho virheellinen syöte, valitse 1 tai 2.\n";
				virhe = true;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (virhe);
	}
	return (palautus);
}

// tarkistaa onko houne vapaa ja palauttaa booleanin sen mukaan
bool	onko_vapaa(Hotelli* huoneet, int hnro)
{
	if (huoneet[hnro].varattu == false)
		return false;
	else
		return true;
}

// arpoo huone numeron käyttäjälle ja tarkistaa samalla onko huone vapaa. Palauttaa arvotun huoneen
int		arvonta(int hkoko, int h_maara, Hotelli* hotellihuoneet)
{
	int huone, i;
	bool varattu = false;

	i = 0;
	//arpoo huoneita niin kauan kunnes vapaa huone arvotaan ja ilmoittaa kun arvontaa on yritetty huoneiden määrän verran ettei vapaita huone tyyppejä on
	do 
	{
		varattu = false;
		if (hkoko == 1)
		{
			huone = rand_nro(40, (h_maara - 40) / 2 + 40);
			if (onko_vapaa(hotellihuoneet, huone))
			{
				varattu = true;
				i++;
			}
			if (i == (h_maara - 40 / 2))
			{
					cout << "Valitettavasti kaikki yhden hengen huoneet ovat varattuja. Kahden hengen huoneita on viela vapaana!\n";
					return (NULL) ;
			}
		}
		else
		{
			huone = rand_nro((h_maara - 40) / 2 + 40, h_maara);
			if (onko_vapaa(hotellihuoneet, huone))
			{
				varattu = true;
				i++;
			}
			if (i == (h_maara - 40 / 2))
				{
					cout << "Valitettavasti kaikki kahden hengen huoneet ovat varattuja. Yhden hengen huoneita on viela vapaana!\n";
					return (NULL) ;
				}
		}
	} while (varattu);

	return (huone);
}

// Laskee kokonaishinnan varaukselle, arpoo ensiksi saako käyttäjä alennuksen. Alennukset ja houne hinnat on määritetty vakiona header filessä.
double	huoneen_hinta(int hkoko, int yot)
{
	int arpa, ale = 0;
	double hinta;

	arpa = rand_nro(1, 30);
	// n.30% mahdollisuus 10% alennukseen
	if (arpa <= 25 && arpa >= 15)
		ale = 1;
	// n.15% mahdollisuus 20% alennukseen
	else if (arpa <= 30 && arpa >= 25)
		ale = 2;
	if (ale == 1)
		cout << "\nOnneksi olkoon sait 10% alennuksen!\n";
	if (ale == 2)
		cout << "\nOnneksi olkoon sait 20% alennuksen!\n";
	if (hkoko == 1)
		hinta = (h1_hinta * yot) * alennus[ale];
	else
		hinta = (h2_hinta * yot) * alennus[ale];
	return (hinta);
}


// Poistaa varauksen nollaamalla sen kaikki tiedot
Hotelli	poista_varaus(Hotelli hotellihuone)
{
	hotellihuone.hinta = 0;
	hotellihuone.hkoko = 0;
	hotellihuone.hnro = 0;
	hotellihuone.p_maara = 0;
	hotellihuone.varausnro  = 0;
	hotellihuone.nimi = '\0';
	hotellihuone.varattu = false;
	return (hotellihuone);
}