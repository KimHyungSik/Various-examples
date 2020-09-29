import pandas as pd
import numpy as np
from konlpy.tag import Okt
from tensorflow.keras.preprocessing.text import Tokenizer
from tensorflow.keras.preprocessing.sequence import pad_sequences
from sklearn.ensemble import RandomForestClassifier

okt = Okt()

order_data = pd.read_excel('./order_semple.xlsx', header=0)
order_data['description'] = order_data['description'].str.replace("[^ㄱ-ㅎㅏ-ㅣ가-힣 ]","")

stopwords = ['의','가','이','은','들','는','좀','잘','걍','과','도','를','으로','자','에','와','한','하다','저기요','주세요']

X_train = []
for sentence in order_data['description']:
    temp_X = []
    temp_X = okt.morphs(sentence, stem=True) # 토큰화
    temp_X = [word for word in temp_X if not word in stopwords] # 불용어 제거
    X_train.append(temp_X)

y_train = np.array(order_data['order'])

tokenizer = Tokenizer()
tokenizer.fit_on_texts(X_train)

tokenizer = Tokenizer(5, oov_token = 'OOV')
tokenizer.fit_on_texts(X_train)
X_train = tokenizer.texts_to_sequences(X_train)
X_train = pad_sequences(X_train, maxlen = 5)

rnd_clf = RandomForestClassifier(n_estimators=500, n_jobs=-1)
rnd_clf.fit(X_train,y_train)

def rndModel(new_sentence):
  global order_data
  text = new_sentence
  new_sentence = okt.morphs(new_sentence, stem=True) # 토큰화
  new_sentence = [word for word in new_sentence if not word in stopwords] # 불용어 제거
  encoded = tokenizer.texts_to_sequences([new_sentence]) # 정수 인코딩
  pad_new = pad_sequences(encoded, maxlen = 5) # 패딩
  score = float(rnd_clf.predict(pad_new)) # 예측
  tempData = pd.DataFrame([[text,str(int(score))]], columns={'order', 'description'})
  order_data = order_data.append(tempData, ignore_index=True)
  print(rnd_clf.predict(pad_new))

def dataWrite():
      order_data.to_excel('./order_semple.xlsx', index=False)


while(1):
    temp = input()
    if(temp == 'saveData'):
        dataWrite()
    elif(temp =='stopModel'):
        break
    else:
        rndModel(temp)
