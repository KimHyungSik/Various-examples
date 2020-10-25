import pyaudio
import numpy as np
import requests
import wave
import json

#audio set
RATE = 16000
CHUNK = 256
CHUNK_text = "256"
WAVE_OUTPUT_FILENAME = "output.wav"

#for kakao setting
kakao_speech_url = "https://kakaoi-newtone-openapi.kakao.com/v1/recognize"
rest_api_key = "51712b5e92f993719878dc18fdb305d6";

headers = {
    "Content-Type" : "application/octet-stream",
    "X-DSS-Service" : "DICTATION",
    "Authorization" : "KakaoAK " + rest_api_key,
}

#pyAudio 설정
audio = pyaudio.PyAudio()

player = audio.open(format=pyaudio.paInt16, channels=1, rate=RATE, output=True,
frames_per_buffer=CHUNK)
stream = audio.open(format=pyaudio.paInt16, channels=1, rate=RATE, input=True, frames_per_buffer=CHUNK)
stt_stream = audio.open(format=pyaudio.paInt16, channels=1, rate=RATE, input=True, frames_per_buffer=CHUNK)

for i in range(int(20*RATE/CHUNK)): #do this for 10 seconds
    data = np.fromstring(stream.read(CHUNK), dtype=np.int16)
    data = int(np.average(np.abs(data)))
    frames = []
    #일정 소음 이상일 시 음성인식
    if data >= 1000:
        print("start")
        for j in range(int((int(20 * RATE / CHUNK))/4)):
            pointer = stt_stream.read(CHUNK)
            frames.append(pointer)

        #파일저장
        waveFile = wave.open(WAVE_OUTPUT_FILENAME, 'wb')
        waveFile.setnchannels(1)
        waveFile.setsampwidth(audio.get_sample_size(pyaudio.paInt16))
        waveFile.setframerate(RATE)
        waveFile.writeframes(b''.join(frames))
        waveFile.close()

        with open('output.wav', 'rb') as fp:
            framesData = fp.read()
        try:
            res = requests.post(kakao_speech_url, headers=headers, data=framesData)
            result_json_string = res.text[res.text.index('{"type":"finalResult"'):res.text.rindex('}') + 1]
            result = json.loads(result_json_string)
            print(result['value'])
        except:
            print("stt error")
        print("end")

stream.stop_stream()
stream.close()
audio.terminate()
