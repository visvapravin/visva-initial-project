import tkinter as tk
from tkinter import ttk, filedialog, messagebox
import pygame
import os

class MusicPlayer:
    def __init__(self, root):
        self.root = root
        self.root.title("Simple Music Player with Equalizer")
        self.root.geometry("800x500")
        self.root.resizable(False, False)
                # Initializing Pygame
        pygame.init()
        pygame.mixer.init()

        # Playlist Frame
        self.playlist_frame = tk.Frame(self.root)
        self.playlist_frame.grid(row=0, column=0, padx=10, pady=10)

        # Playlist Listbox
        self.playlist = tk.Listbox(self.playlist_frame, width=40, height=20)
        self.playlist.pack(fill=tk.BOTH, expand=True)
        self.playlist.bind("<<ListboxSelect>>", self.play_selected)

        # Control Frame
        self.control_frame = ttk.Frame(self.root)
        self.control_frame.grid(row=0, column=1, padx=10, pady=10)

        # Play/Pause button
        self.play_var = tk.StringVar()
        self.play_var.set("Play")
        self.play_pause_button = ttk.Button(self.control_frame, textvariable=self.play_var, command=self.play_pause)
        self.play_pause_button.grid(row=1, column=0, padx=10, pady=10)
                # Skip Backward button
        self.skip_backward_button = ttk.Button(self.control_frame, text="⏪", command=self.skip_backward)
        self.skip_backward_button.grid(row=2, column=0, padx=10, pady=10)

        # Skip Forward button
        self.skip_forward_button = ttk.Button(self.control_frame, text="⏩", command=self.skip_forward)
        self.skip_forward_button.grid(row=3, column=0, padx=10, pady=10)

        # Import Music button
        self.import_button = ttk.Button(self.control_frame, text="Import Music", command=self.import_music)
        self.import_button.grid(row=4, column=0, padx=10, pady=10)
                # Volume Control
        self.volume_var = tk.DoubleVar()
        self.volume_var.set(0.5)
        self.volume_scale = ttk.Scale(self.control_frame, from_=0, to=1, orient="horizontal", variable=self.volume_var, command=self.set_volume)
        self.volume_scale.grid(row=5, column=0, padx=10, pady=10)
        self.volume_label = ttk.Label(self.control_frame, text="Volume")
        self.volume_label.grid(row=6, column=0, padx=10, pady=10)

        # Equalizer Frame
        self.equalizer_frame = ttk.LabelFrame(self.root, text="Equalizer")
        self.equalizer_frame.grid(row=1, column=0, columnspan=2, padx=10, pady=10)

        self.freq_bands = ["60 Hz", "170 Hz", "310 Hz", "600 Hz", "1 kHz", "3 kHz", "6 kHz", "12 kHz", "14 kHz", "16 kHz"]
        self.sliders = []

        for i, band in enumerate(self.freq_bands):
            label = ttk.Label(self.equalizer_frame, text=band)
            label.grid(row=0, column=i, padx=5, pady=5)
            slider = ttk.Scale(self.equalizer_frame, from_=-10, to=10, orient="vertical", command=self.update_equalizer)
            slider.set(0)
            slider.grid(row=1, column=i, padx=5, pady=5)
            self.sliders.append(slider)
                    # Current song label
        self.current_song = ""

        # Paused variable to check if the song is paused or not
        self.paused = False

    def play_selected(self, event):
        selected_song = self.playlist.get(self.playlist.curselection())
        self.current_song = selected_song
        pygame.mixer.music.load(self.current_song)
        pygame.mixer.music.play()
        self.play_var.set("Pause")

    def play_pause(self):
        if self.paused:
            pygame.mixer.music.unpause()
            self.paused = False
            self.play_var.set("Pause")
        else:
            pygame.mixer.music.pause()
            self.paused = True
            self.play_var.set("Play")
    def skip_backward(self):
        selection = self.playlist.curselection()
        if selection:
            prev_song_index = int(selection[0]) - 1
            if prev_song_index >= 0:
                prev_song = self.playlist.get(prev_song_index)
                self.current_song = prev_song
                pygame.mixer.music.load(self.current_song)
                pygame.mixer.music.play()
                self.play_var.set("Pause")
            else:
                messagebox.showwarning("Warning", "This is the first song.")
        else:
            messagebox.showerror("Error", "No song is selected.")
    def skip_forward(self):
        selection = self.playlist.curselection()
        if selection:
            next_song_index = int(selection[0]) + 1
            if next_song_index < self.playlist.size():
                next_song = self.playlist.get(next_song_index)
                self.current_song = next_song
                pygame.mixer.music.load(self.current_song)
                pygame.mixer.music.play()
                self.play_var.set("Pause")
            else:
                messagebox.showwarning("Warning", "This is the last song.")
    def set_volume(self, val):
        volume = float(val)
        pygame.mixer.music.set_volume(volume)

    def import_music(self):
        file_paths = filedialog.askopenfilenames()
        for file_path in file_paths:
            if file_path not in self.playlist.get(0, tk.END):
                self.playlist.insert(tk.END, file_path)

    def update_equalizer(self, val):
        # Placeholder for equalizer functionality
        # Implement equalizer effect processing here
        pass

# Main program starts here using the class MusicPlayer and the root window
root = tk.Tk()
MusicPlayer(root)

# Run the main window loop
root.mainloop()
