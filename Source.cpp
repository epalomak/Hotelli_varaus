/****************************************************/
/* @ Author: Eino Palomaki                          */
/* @ Create Time: 2022-11-16 10:00:43               */
/* @ Modified by: Eino Palomaki                     */
/* @ Modified time: 2022-12-12 11:45:12             */
/****************************************************/

#include"header.h"

int		main()
{
	setlocale(LC_ALL, "fi_FI.UTF-8");
	int valinta, h_maara, vapaana;
	bool virhe, jatketaan = true;

	//arvotaan huoneiden määrä rand_nro apuohjelmalla ja kerrotaan se kahdella
	//jotta huoneiden määrä on aina parillinen 
	h_maara = rand_nro(21, 150) * 2;

	Hotelli hotellihuoneet[max_huoneet];
	vapaana = h_maara - 40;

	// looppi joka pyörittää ohjelmaa niin kauan kunnes käyttäjä sen lopettaa/hotelli on täynnä
	while (jatketaan)
	{
		//tarkistus tarkistaa syötteen aliohjelmassa
		valinta = tarkistus(1);
		// 1 = varauksen teko
		if (valinta == 1)
		{	
			//tarkistaa onko huoneita vapaana
			if (vapaana == 0)
			{
				cout << "Hotelli on valitettavasti tayteen varattu!\n";
				jatketaan = false;
			}
			else
				huoneen_varaus(vapaana, h_maara, hotellihuoneet); 
		}
		// 2 = varauksen peruutus
		else if (valinta == 2)
		{
			//tarkistetaan onko varauksia tehty
			if (vapaana == h_maara - 40)
			{
				cout << "Yhtään varausta ei ole tehty.\n\n";
				//continue vie takaisin while looppiin, jotta aliohjelmaa varauksen_peruutus ei kutsuta
				continue;									
			}
			varauksen_peruutus(hotellihuoneet, h_maara,vapaana); 
		}
		//3 = varauksen tarkistelu
		else if (valinta == 3) 
		{
			//tarkistetaan onko varauksia tehty
			if (vapaana == h_maara - 40)
			{
				cout << "Yhtään varausta ei ole tehty.\n\n";
				continue;
			}
			varauksen_tarkastelu(hotellihuoneet, h_maara);
		}
		// 4 = ohjelman lopetus
		else if (valinta == 4)
			jatketaan = false;
	}

	cout << "\nTervetuloa uudestaan!\n\n";

	return 0;
}