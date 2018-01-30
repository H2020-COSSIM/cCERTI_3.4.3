# cCERTI - COSSIM-modified CERTI version. 

cCERTI is a modified version of CERTI that integrates the COSSIM framework. The cCERTI extends the scalability of CERTI to more than 500 nodes. It should be noted that cCERTI can be used independently of COSSIM as a standalone package incorporating all the changes that have been integrated to the official CERTI 3.4.3 release.

## Differences between cCERTI and official CERTI 3.4.3 version

A second constructor is implemented to support up to 3 different HLA servers according to the number of simulated nodes. Specifically, the following files have been changed:

- include/hla-1_3/RTIambServices.hh
- libRTI/hla-1_3/RTIambassador.cc

In addition SynchServer is implemented in order to initiate the HLA Federations.

Finally, the federation file is created to declare the COSSIM Federation description:
- Federation.fed


## Compiling and executing cCERTI

Please read the [Installation Guide](CERTI_Install.pdf) file.

## Using cCERTI in the context of the COSSIM simulation framework

Please refer to [COSSIM _framework](https://github.com/H2020-COSSIM/COSSIM_framework) repository for all required instructions.

## Licensing

Refer to the [LICENSE](LICENSE) and [COPYING](COPYING.txt) files included. Individual license may be present in different files in the source codes.

#### Authors

* Nikolaos Tampouratzis (ntampouratzis@isc.tuc.gr)

Please contact for any questions.

## Acknowledgments

Code developed for the H2020-COSSIM project.

