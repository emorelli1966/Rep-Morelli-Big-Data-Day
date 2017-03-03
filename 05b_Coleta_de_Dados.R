#diretório contendo primeira lista
setwd("C:/Users/eduar/Dropbox/aInfnet/Infnet_Pos_Big_Data/Turma Sábados/Blocos/Bloco A 2017/M1/Aulas_03e04_04_mar/Datasets/dcase2013_event_detection_testset_OS")

listaArqs = list.files(pattern = ".*.txt")

#assumindo dados separados por tab e sem cabeçalho  
lista = lapply(listaArqs, function(x)read.table(x, header=F)) 

#diretório contendo segunda lista
setwd("C:/Users/eduar/Dropbox/aInfnet/Infnet_Pos_Big_Data/Turma Sábados/Blocos/Bloco A 2017/M1/Aulas_03e04_04_mar/Datasets/OS-IRCCYN/annotation")

listaArqs = list.files(pattern = ".*.txt")

lista2 = lapply(listaArqs, function(x)read.table(x, header=F)) 


#criando data frames
df1 = do.call("rbind", lista) 

df2 = do.call("rbind", lista2) 

#unindo
df = rbind(df1, df2)

#nomes de colunas
names(df) <- c("Inicio", "Fim","Tipo")

#quarta coluna com diferença
df$duracao = (df$Fim - df$Inicio)

#Gravando csv
setwd("C:/Users/eduar/Dropbox/aInfnet/Infnet_Pos_Big_Data/Turma Sábados/Blocos/Bloco A 2017/M1/Aulas_03e04_04_mar/Datasets")

write.csv(df, file = "Medidas.csv",row.names=FALSE) 
