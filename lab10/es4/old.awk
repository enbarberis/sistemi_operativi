BEGIN{
#	print longest
#	print shortest
#	print num_search
#	print verbose
#	print dictionary
#	print inp_file

	#carico dizionario
	while(getline < dictionary)
	{
		riga=$0;
		parola=$1;
		parola=tolower(parola);
		gsub(":", "", parola);	
		i=0;

		printf("La parola '%s' ha le seguenti traduzioni:\n", parola);
		
		while(riga != "#")
		{
			getline < dictionary;
			if($1 != "#")
			{
				riga=tolower($1);
				printf("%s\n", riga);
				traduzione[parola, i]=riga;
				i++;
			}
		}
	}

	exit

	#traduco
	while(getline < inp_file)
	{
		for(i=1; i<=NF; i++)
		{
			parola = tolower($i);
			
			if(traduzione[parola, 0] != "")
			{	
				if(num_search != -1)
				{
					print traduzione[parola, num_search-1];
				}
				else if(longest)
				{
					for(i=0; length(traduzione[parola, i]) > 0; i++)
					{
						print traduzione[parola, i]
					}
				}
				else if(shortest)
				{
					
				}
			}
			else
			{
				if(verbose)
				{
					print parola " (WARNING: no traduction for '" parola "')"
				}
				else
				{
					print parola
				}
				
			}
		}
	}

}
