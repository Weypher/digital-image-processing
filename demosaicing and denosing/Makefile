all:
	g++ -ggdb -Wall bilinear.cpp -o bilinear
	g++ -ggdb -Wall mhc.cpp -o mhc
	g++ -ggdb -Wall histogram1.cpp -o histogram1
	g++ -ggdb -Wall histogram2.cpp -o histogram2
	g++ -ggdb -Wall denoising_Uni.cpp -o denoising_Uni
	g++ -ggdb -Wall denoising_Gas.cpp -o denoising_Gas
	g++ -ggdb -Wall denoising_Bilateral.cpp -o denoising_Bilateral
	g++ -ggdb -Wall nlm.cpp -o nlm

# 	g++ -ggdb -Wall serverB.cpp -o serverB
# 	g++ -ggdb -Wall aws.cpp -o aws
# 	g++ -ggdb -Wall client.cpp -o client

.PHONY: bilinear mhc histogram2 histogram1 denoising_Bilateral denoising_Gas denoising_Uni Dogout_bilinear nlm clean

bilinear:
	./bilinear ./image/Dog.raw ./result/Dogout_bilinear.raw 1 600 532 3

mhc:
	./mhc ./image/Dog.raw ./result/Dogout_MHC.raw 1 600 532 3

histogram1:
	./histogram1 ./image/Toy.raw ./result/Toy_histogram_MethodA.raw 3 400 560 3

histogram2:
	./histogram2 ./image/Toy.raw ./result/Toy_histogram_MethodB.raw 3 400 560 3

denoising_Uni:
	./denoising_Uni ./image/Corn_noisy.raw ./result/Cornout_Uni.raw 1 320 320 1 ./image/Corn_gray.raw

denoising_Gas:
	./denoising_Gas ./image/Corn_noisy.raw ./result/Cornout_Gas.raw 1 320 320 1 ./image/Corn_gray.raw

denoising_Bilateral:
	./denoising_Bilateral ./image/Corn_noisy.raw ./result/Cornout_Bil.raw 1 320 320 1 ./image/Corn_gray.raw

nlm:
	./nlm ./image/Corn_noisy.raw ./image/Corn_gray.raw ./result/Corn_NLM.raw 1 320 320

clean:
	rm bilinear mhc histogram2 histogram1 denoising_Bilateral denoising_Gas denoising_Uni Dogout_bilinear nlm