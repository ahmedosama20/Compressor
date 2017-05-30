# Compressor
Bzip2-like file compressor using the Burrows-Wheeler method

# Algorithm Details
First, the burrows wheeler transform is applied to the input text.

This transform first sorts all the rotations of the input text in lexicographical order, then outputs the Primary Index which is the location of the original string in the sorted rotations, and outputs a string L, which consists of the last letter of each rotation.

The Primary Index and the string L are sufficient to reverse the transform because from them we can deduce the original order of the symbols in the original string.

The transform is reversed by sorting the string L and recording the old location and the new location of each character in string L in the process.

An array T is created such that:

T[old location] = new location

Then the original text is restored using the algorithm:


        Index = Primary Index;
        For(P = SizeOfText – 1; P >= 0; P--)
        {
        OriginalText[P] = L[Index];
        Index = T[Index];
        }


The Burrows-Wheeler transform produces a string where there are high local concentrations
(long runs) of symbols, thus making compressing this string with Move-To-Front and Run Length
Encoding very efficient.

Second, the Move-To-Front transform with Run Length Encoding is applied to the result the
Burrows-Wheeler transform.
The Move-To-Front transform creates an initially sorted array of
all symbols used in the input message then starts replacing symbols with their index in the
array.
When a symbol is replaced with its index, this symbol is moved to the front of the array
of symbols (thus its new index becomes 0), that way in a long run of symbols, the result
becomes “I 0 0 0 0 0 0 0 0 0 0 0 0 … “Where I is the initial position of that symbol in the array.

The long runs of 0s is then compressed with Run Length Encoding by writing the number of 0s
in bijective base-3 (Bzip2 uses bijective base-2, but we got better compression when we used
bijective base-3).
The reversal of the Move-To-Front transform is simply a matter of reversing
the steps.

Third, the result of the Move-To-Front transform is encoded with Adaptive Arithmetic Coding.

## To sum up, the steps of our compression are:
1 -Burrows-Wheeler-Transform

2 -Move-To-Front and Run Length Encoding

3 - Adaptive Arithmetic Coding

And the steps of decompression are:

1 - Adaptive Arithmetic Decoding

2 - Inverse Move-To-Front and Inverse Run Length Encoding

3 – Inverse Burrows-Wheeler-Transform


# Encoded File Format
The compressed file first contains a sparse array of the symbols in the original file. The
symbols(256) are divided to 16 ranges.

The first 16 bits of the file are used as flags to indicate
whether the symbols from the ith range are used.

Then for every used range, 16 bits are
written that indicate whether the jth symbol of the ith range is used.

Following is 24 bits which contain the Primary Index used in the inverse-Burrows-Wheeler.

Following is the output of the Adaptive Arithmetic Coding.

Thus, the compressed file contains all the needed information for the decoder to successfully
decompress the file.

# Results
Total uncompressed size in bytes: 6535598
Total compressed size in bytes: 918734
Total compression ratio: 7.1137

# Important Note
When building the project, please build it with the “Release” configuration, not with “Debug”.

When it is built with the “Release” configuration, it finishes execution in a few seconds, but
when built with the “Debug” configuration, it can take a few hours.
