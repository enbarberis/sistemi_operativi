BEGIN{

#	print longest
#	print shortest
#	print num_search
#	print verbose
#	print dictionary
#	print inp_file


	#LOAD DICTIONARY
	RS="#\n"
	FS="\n"

	while (getline < dictionary)
	{
		word = tolower($1);
		gsub(":", "", word);
		#printf("La parola '%s' ha le seguentui traduzioni:\n", parola);
		
		for(i=2; i<NF; i++)
		{
			translation[word, i-2]=$i;
			#printf("traduzione[%s, %d]=%s\n", parola, i-2, $i);
		}
	}

	#TRANSLATION
	RS="\n"
	FS=" "

	while (getline < inp_file)
	{
		#for every line in text
		for(i=1; i<=NF; i++)
		{
			word = tolower($i);

			#for very word
			if(translation[word, 0] != "")
			{
				#if there is at least one translation
				#printf("%s ", translation[word, 0]);

				if(num_search != -1)
				{
					if(translation[word, num_search-1] != "")
					{
						printf("%s ", translation[word, num_search-1]);
					}
					else
					{
						printf("%s ", word);
					}
				}
				if(longest)
				{
					printf("\nTraducendo %s\n", word);
					long_trans = "";
					i=0;
					while(translation[word, i] != "")
					{
						printf(">>>%s %d\n", translation[word, i], length(translation[word, i]));
						if(length(translation[word, i]) > length(long_trans))
						{
							long_trans = translation[word, i];
						}

						i++;
					}
					printf("%s ", long_trans);
					system("sleep 5");
				}
			}
			else
			{
				if(verbose)
				{
					printf("%s -> NO TRANSLATION\n", word);
				}
				else
				{
					printf("%s ", word);
				}
			}
		}
	}

	printf("\n\n");
}
