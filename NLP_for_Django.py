import joblib
from konlpy.tag import Okt

okt = Okt()
tokenizer = joblib.load("./token.pkl")
tree_clf = joblib.load("./nlp_sample.pkl")
pad_sequences = joblib.load("./pad_sequences.pkl")

#띄어쓰기 함수
def spacing_okt(wrongSentence):
    tagged = okt.pos(wrongSentence)
    corrected = ""
    for i in tagged:
        print(i)
        if i[1] in ('Josa', 'PreEomi', 'Eomi', 'Suffix', 'Punctuation', 'Modifier'):
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
  stopwords = ['의', '로', '가', '이', '은', '들', '는', '좀', '잘', '걍', '과', '도', '를', '으로', '자', '에', '와', '한', '하다', '저기요','주세요', '할게요']
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
      print(tree_clf.predict(pad_new))

while(1):
    temp = input()
    if(temp =='stopModel'):
        joblib.dump(tokenizer, 'token.pkl')
        joblib.dump(tree_clf, 'nlp_sample.pkl')
        joblib.dump(rndModel, 'rndModel')
        break
    else:
        rndModel(temp)
