#include <iostream>

typedef unsigned char uchar;
typedef unsigned int uint;

int d = 256; // Grootte van het alfabet: ASCI
int Q = 997; // Ons priem getal

// Via horner de hash van een string berekenen.
int hash(const uchar* str, uint m) {
    int h = 0;
    for (uint j = 0; j < m; j++)
        h = (d * h + str[j]) % Q;
	
    return h;
}

bool check_same(const uchar* str, uint pos, const uchar* pattern, uint m) {
    // We kijken of het stukje string dat begint op positie pos in 'str'
    // gelijk is aan het pattern.
	
    // Bij een Monte Carlo algoritme returnen we hier altijd true.
    // return true;
	
    // Bij een Las vegas algortime doen we een expliciete check.
    for (uint i = 0; i < m; i++)
        if (str[pos + i] != pattern[i])
            return false;
	
    return true;
}

// Zal de positie returnen waar pattern voorkomt in de text.
void search(const uchar* text, uint n, const uchar* pattern, uint m) {
    // We berekenen een hash waarde voor ons pattern.
    int pattern_hash = hash(pattern, m);
	
    // We berekenen de initiele hash T1.
    int text_hash = hash(text, m); // we berekenen een hash voor lengte m !!! (dus niet de hele haystack!)
	
    // We hebben d^(m-1) % Q nodig.
    // Onderstaande for lus is niks meer dan de machtsverheffing, gemodulo'd.
    int dm = 1;
    for (uint i = 0; i < m - 1; i++)
        dm = (dm * d) % Q;
	
	// Patroon over de text laten gaan
    for (uint i = 0; i <= n-m; i++) {
		
        // Vergelijk de hashes.
        if (text_hash == pattern_hash){
			int j=0;
			while(text[i+j] == pattern[j]){
				j++;
			}
			if(j==m){
				std::cout<<i<<std::endl;
			}
        }
		
		// ipv een hash te berekenen voor _alle_ deelstrings, leiden we de hash af uit de vorige. (anders zou het O(mn) zijn)
        // 1. We trekken er het eerste karakter vooraan af.
        // 2. We tellen het nieuwe karakter erbij op.
        text_hash = (((text_hash + Q*(d-1) - text[i]*(dm % Q)) % Q)*d + text[i+m])%Q;
    }
}

int main() {
    const uchar text[] = "abeta beta charly alfa";
    const uchar pattern[] = "beta";
	
    search(text, 23, pattern, 4);
    
	
    return 0;
}