import pyaudio
import numpy as np
import wave

RATE    = 16000
CHUNK   = 256
WAVE_OUTPUT_FILENAME = "output.wav"

p = pyaudio.PyAudio()

player = p.open(format=pyaudio.paInt16, channels=1, rate=RATE, output=True,
frames_per_buffer=CHUNK)
stream = p.open(format=pyaudio.paInt16, channels=1, rate=RATE, input=True, frames_per_buffer=CHUNK)
stt_stream = p.open(format=pyaudio.paInt16, channels=1, rate=RATE, input=True, frames_per_buffer=CHUNK)

for i in range(int(20*RATE/CHUNK)): #do this for 10 seconds
    data = np.fromstring(stream.read(CHUNK), dtype=np.int16)
    data = int(np.average(np.abs(data)))
    frames = []
    if data >= 1100:
        for j in range(int((int(20 * RATE / CHUNK))/2)):
            pointer = stt_stream.read(CHUNK)
            frames.append(pointer)
            wf = wave.open(WAVE_OUTPUT_FILENAME, 'wb')
            wf.setnchannels(1)
            wf.setsampwidth(p.get_sample_size(pyaudio.paInt16))
            wf.setframerate(RATE)
            wf.writeframes(b''.join(frames))
            wf.close()

stream.stop_stream()
stream.close()
p.terminate()
