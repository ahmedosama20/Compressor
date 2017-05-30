#include "Compressor.h"

int main()
{
	Compressor compressor;
	ofstream stats("statistics.txt");
	string originalfilenames[20] = {
		"All's Well that Ends Well.txt",
		"Anthony and Cleopatra.txt",
		"As You Like It.txt",
		"Coriolanus.txt",
		"Cymbeline.txt",
		"Hamlet, Prince of Denmark.txt",
		"King Lear.txt",
		"Love's Labour's Lost.txt",
		"Measure for Measure.txt",
		"Much Ado About Nothing.txt",
		"Othello, the Moor of Venice.txt",
		"Pericles, Prince of Tyre.txt",
		"The Merchant of Venice.txt",
		"The Merry Wives of Windsor.txt",
		"The Taming of the Shrew.txt",
		"The Tempest.txt",
		"The Two Gentlemen of Verona.txt",
		"The Winter's Tale.txt",
		"Troilus and Cressida.txt",
		"Twelfth-Night; or What You Will.txt"
	};
	string compressedfilenames[20] = {
		"All's Well that Ends Well.bwt",
		"Anthony and Cleopatra.bwt",
		"As You Like It.bwt",
		"Coriolanus.bwt",
		"Cymbeline.bwt",
		"Hamlet, Prince of Denmark.bwt",
		"King Lear.bwt",
		"Love's Labour's Lost.bwt",
		"Measure for Measure.bwt",
		"Much Ado About Nothing.bwt",
		"Othello, the Moor of Venice.bwt",
		"Pericles, Prince of Tyre.bwt",
		"The Merchant of Venice.bwt",
		"The Merry Wives of Windsor.bwt",
		"The Taming of the Shrew.bwt",
		"The Tempest.bwt",
		"The Two Gentlemen of Verona.bwt",
		"The Winter's Tale.bwt",
		"Troilus and Cressida.bwt",
		"Twelfth-Night; or What You Will.bwt"
	};
	int totaluncompsize = 0, totalcompsize = 0;

	for (int i = 0; i < 20; i++)
	{
		int uncompsize, compsize;

		string spaces = "";
		int j = originalfilenames[i].size();
		for (; j < 36; j++)
			spaces += ' ';
		compressor.Compress("originalfiles/"+originalfilenames[i], "encodedfiles/"+compressedfilenames[i], &uncompsize, &compsize);
		cout << originalfilenames[i] << spaces << "Uncompressed size: " << uncompsize << " " << "Compressed size: " << compsize << " " << "Compression ratio: " << (double)uncompsize / compsize << endl;
		stats << originalfilenames[i] << spaces << "Uncompressed size: " << uncompsize << " " << "Compressed size: " << compsize << " " << "Compression ratio: " << (double)uncompsize / compsize << endl;
		compressor.Decompress("encodedfiles/" + compressedfilenames[i], "decodedfiles/" + originalfilenames[i]);
		totaluncompsize += uncompsize;
		totalcompsize += compsize;
	}

	cout << endl <<"Total uncompressed size: " << totaluncompsize << " " << "Total compressed size: " << totalcompsize << " " << "Total compression ratio: " << (double)totaluncompsize / totalcompsize << endl;
	stats << endl <<"Total uncompressed size: " << totaluncompsize << " " << "Total compressed size: " << totalcompsize << " " << "Total compression ratio: " << (double)totaluncompsize / totalcompsize << endl;
	stats.close();
	cin.get();
}

