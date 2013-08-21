Steganography
=============

“Steganography is the art and science of writing hidden messages in such a way that no one, apart from the sender and intended recipient, suspects the existence of the message, a form of security through obscurity.”

Huffman Text Compression
========================
* Many a times we want to e-mail a file of large sizes (>25 MB).
* Most of the services support the files of size upto 25 MB. Thus, it becomes necessary to somehow compress a file.
* Huffman Compression on an average compresses the file by 70% (by test cases).
* Also, services don’t allow “.exe” files to be mailed for security purposes. We can compress an “.exe” file and send it through e-mail without the knowledge of service provider (cant be done by “.tar”, “.tar.gz” or “.zip”.
* The compressed file can be de-extracted back to get the original file back

Steganography
=============
* Text message can be hidden in a image with non- lossy compression.
* A small image can be hidden in a larger image with non-lossy compression.
* Huffman encoding is done to improve the payload.
* Standard LSB insertion algorithm is used.
* Password is used to secure the message.
* There is no change in the size of the cover image.
* The change in the image cannot be detected by a normal human eye.

HOW TO RUN
----------
* open the project in code::block
* provide path for opencv header files in code::block
* run the program and provide required input paths
