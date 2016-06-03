#include <iostream>
#include <fstream>
#include <string>
using namespace std;

pair<string,float> ** probabilities(pair<string, int> * input) {
	// Expect an array of size three, with the first value representing homozygous dominant
	// Second represents heterozygous, third represents homozygous recessive

	// Output will be of size 3x3, representing all possible pairings
	pair<string, float> ** output = new pair<string, float>*[3];
	for (unsigned int i = 0; i < 3; i++) {
		output[i] = new pair<string, float>[3];
	}

	// Draw pool size for probability calculations
	float total = input[0].second + input[1].second + input[2].second;

	for (unsigned int i = 0; i < 3; i++) {
		// Looping through for each pair of parents' probability
		for (unsigned int j = 0; j < 3; j++) {
			// represents pairing - should be something like kk, km, kn, etc
			output[i][j].first = input[i].first + input[j].first;

			// Probability: chance of each individual being drawn, which for the first value is i/total
			// Second parent cannot be identical to first (no offspring with yourself)
			// So if they're drawing from the same pool, the chance is (group - 1)/(total - 1)
			// While for different groups it becomes (group)/(total - 1)
			if (i == j) {
				output[i][j].second = (input[i].second / total) * ((input[j].second - 1) / (total - 1));
			}
			else {
				output[i][j].second = (input[i].second / total) * (input[j].second / (total - 1));
			}
		}
	}


	return output;
}

int main() {

	// k is homozygous dominant
	// m is heterozygous
	// n is homozygous recessive
	unsigned int k, m, n;

	pair<string, int> * input;
	input = new pair<string, int>[3];

	cin >> k >> m >> n;

	input[0] = make_pair("K", k);
	input[1] = make_pair("M", m);
	input[2] = make_pair("N", n);

	// We are looking at the probability that a random pair drawn from this group will
	// produce offspring with a dominant phenotype
	pair<string, float> ** probs;
	probs = probabilities(input);

	// The final probability of a dominant phenotype is the sum of the parentage
	// probabilities * their chance of dominant offspring
	float total = 0.0;

	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 3; j++) {
			cout << probs[i][j].first << "\t" << probs[i][j].second << endl;
			total += probs[i][j].second;
		}
	}
	cout << "Total probability: " << total << endl;

	total = 0.0;

	total += probs[0][0].second;				// KK
	total += probs[0][1].second;				// KM
	total += probs[0][2].second;				// KN
	total += probs[1][0].second;				// MK
	total += probs[1][1].second * (3.0 / 4.0);	// MM - 75% chance of dominant phenotype
	total += probs[1][2].second / 2.0;			// MN - 50% chance of dominant phenotype
	total += probs[2][0].second;				// NK
	total += probs[2][1].second / 2.0;			// NM - 50% chance of dominant phenotype
	total += probs[2][2].second * 0.0;			// NN - 00% chance of dominant phenotype

	cout << "Probability of dominant gene: " << total << endl;
	
	return 0;
}