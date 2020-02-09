from matplotlib import pyplot as plt 
from matplotlib import style 
import numpy as np

style.use('ggplot')

N, ABB, AVL = np.loadtxt('data.txt',unpack=True,delimiter = ';')

N, ABB, AVL = zip(*sorted(zip(N, ABB, AVL)))

plt.plot(N,ABB,label='ABB')
plt.scatter(N,ABB,marker='.', color='y')
plt.plot(N,AVL,label='AVL')
plt.scatter(N,AVL,marker='.', color='g')

plt.title('Tree Comparison\nABB vs AVL')
plt.ylabel('Comparisons')
plt.xlabel('Number')
plt.legend()

plt.show()
plt.savefig('grafico.png')