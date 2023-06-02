import matplotlib.pyplot as plt
import pandas as pd


# Carregando os dados do arquivo CSV em DataFrames
df1 = pd.read_csv('data/AVL_insertion.csv')
df2 = pd.read_csv('data/RB_insertion.csv')
df3 = pd.read_csv('data/B1_insertion.csv')
df4 = pd.read_csv('data/B5_insertion.csv')
df5 = pd.read_csv('data/B10_insertion.csv')


x1 = df1.iloc[:, 0]
y1 = df1.iloc[:, 1]

x2 = df2.iloc[:, 0]
y2 = df2.iloc[:, 1]

x3 = df3.iloc[:, 0]
y3 = df3.iloc[:, 1]

x4 = df4.iloc[:, 0]
y4 = df4.iloc[:, 1]

x5 = df5.iloc[:, 0]
y5 = df5.iloc[:, 1]



# Criar um novo gráfico
plt.figure()

# Plotar as curvas
plt.plot(x1, y1, label='AVL')
plt.plot(x2, y2, label='Rubro-Negra')
plt.plot(x3, y3, label='B1')
plt.plot(x4, y4, label='B5')
plt.plot(x5, y5, label='B10')

# Adicionar legendas e rótulos dos eixos
plt.title('Operação: Inserção')
plt.legend()
plt.xlabel('Número de Nós')
plt.ylabel('Operações')

# Exibir o gráfico
plt.savefig('data/grafico_insertion.png')
