import speech_recognition as sr
import pygame

# Init mixer with safe format
pygame.mixer.init(frequency=44100, size=-16, channels=2)

# Load jump sound
jump_sound = pygame.mixer.Sound("jump.wav")

recognizer = sr.Recognizer()
mic = sr.Microphone()

def listen_and_trigger():
    with mic as source:
        recognizer.adjust_for_ambient_noise(source)
        print("🎙 Listening for command...")
        audio = recognizer.listen(source)

    try:
        command = recognizer.recognize_google(audio)
        print(f"🗣 You said: {command}")

        with open("command.txt", "w") as f:
            if "jump" in command.lower():
                print("✅ Jump command sent")
                jump_sound.play()
                f.write("jump\n")
            elif "left" in command.lower():
                print("left commands sent")
                f.write("left\n")
            elif "right" in command.lower():
                f.write("right\n")

    except sr.UnknownValueError:
        print("❌ Could not understand")
    except sr.RequestError:
        print("❌ API error")


# 🔁 Keep listening
if __name__ == "__main__":
    while True:
        listen_and_trigger()
