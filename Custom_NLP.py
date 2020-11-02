import pandas as pd
import numpy as np
from konlpy.tag import Okt
from konlpy.tag import Kkma
from tensorflow.keras.preprocessing.text import Tokenizer
from tensorflow.keras.preprocessing.sequence import pad_sequences
from sklearn.tree import DecisionTreeClassifier
import joblib


okt = Okt()
kkma = Kkma()
order_data = pd.read_excel('./order_semple.xlsx', header=0)
order_data['description'] = order_data['description'].str.replace("[^ㄱ-ㅎㅏ-ㅣ가-힣 ]","")

f = open("text_space_model.txt", 'w', encoding='UTF-8')
for x in order_data['description']:
    f.write(str(x)+"\n")
f.close()


stopwords = ['의','로','가','이','은','들','는','좀','잘','걍','과','도','를','으로','자','에','와','한','하다','저기요','주세요', '할게요']

X_train = []
for sentence in order_data['description']:
    temp_X = okt.morphs(sentence, stem=True) # 토큰화
    temp_X = [word for word in temp_X if not word in stopwords]  # 불용어 제거
    X_train.append(temp_X)

y_train = np.array(order_data['order'])
tokenizer = Tokenizer()
tokenizer.fit_on_texts(X_train)

threshold = 2
total_cnt = len(tokenizer.word_index)   # 전체 단어의 수
rare_cnt = 0                            # 등장 빈도수가 threshold보다 작은 단어의 개수
total_freq = 0                          # 훈련 데이터의 전체 단어 빈도수 총 합
rare_freq = 0                           # 등장 빈도수가 threshold보다 작은 단어의 등장 빈도수의 총 합

# 단어와 빈도수의 쌍(pair)을 key와 value로 받는다.
for key, value in tokenizer.word_counts.items():
    total_freq = total_freq + value

    # 단어의 등장 빈도수가 threshold보다 작으면
    if(value < threshold):
        rare_cnt = rare_cnt + 1
        rare_freq = rare_freq + value

#단어 수가 2이하인 문자 제거 + oov토큰 대비
vocab_size = total_cnt - rare_cnt + 2

tokenizer = Tokenizer(vocab_size, oov_token = 'OOV')
tokenizer.fit_on_texts(X_train)

sequences= tokenizer.texts_to_sequences(X_train)
X_train = tokenizer.texts_to_sequences(X_train)
X_train = pad_sequences(X_train, maxlen = 5)

tree_clf = DecisionTreeClassifier(max_depth=4, random_state=0)
tree_clf.fit(X_train, y_train)

#띄어쓰기 함수
def spacing_okt(wrongSentence):
    tagged = okt.pos(wrongSentence)
    corrected = ""
    for i in tagged:
        print(i)
        if i[1] in ('Josa', 'PreEomi', 'Eomi', 'Suffix', 'Punctuation'):
            corrected += i[0]
        else:
            corrected += " "+i[0]
    if corrected[0] == " ":
        corrected = corrected[1:]
    return corrected

#처음 보는 문장 검사
def check_new_text(text):
    for x in text:
        if int(x) > 1:
            return True
    return False

def rndModel(new_sentence):
  global order_data
  new_sentence = spacing_okt(new_sentence)
  print(new_sentence)
  new_sentence = new_sentence.replace("[^ㄱ-ㅎㅏ-ㅣ가-힣 ]", "")
  text = new_sentence
  # 토큰화
  new_sentence = okt.morphs(new_sentence, stem=True)

  # 불용어 제거
  new_sentence = [word for word in new_sentence if not word in stopwords]

  # 정수 인코딩
  encoded = tokenizer.texts_to_sequences([new_sentence])
  print(new_sentence)
  print(encoded)

  if check_new_text(encoded[0]) == False:
      print("이해할수 없는 단어")

  else:
      # 패딩
      pad_new = pad_sequences(encoded, maxlen=5)
      print(pad_new)

      #예측
      score = float(tree_clf.predict(pad_new))
      tempData = pd.DataFrame([[text,int(score)]], columns={'order', 'description'})
      order_data = order_data.append(tempData, ignore_index=True)
      print(tree_clf.predict(pad_new))

def dataWrite():
      order_data.to_excel(excel_writer='order_semple.xlsx', index=False)


while(1):
    temp = input()
    if(temp == 'saveData'):
        dataWrite()
    elif(temp =='stopModel'):
        joblib.dump(tokenizer, 'token.pkl')
        joblib.dump(tree_clf, 'nlp_sample.pkl')
        break
    else:
        rndModel(temp)
