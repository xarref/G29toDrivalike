import pygame
from sys import exit as _exit

#handles events 
def handleEvents(events):
    exitGame = False
    for event in events:
        if event.type == pygame.QUIT:
            pg_window.close()


def write(display:pygame.display, text:str, pos:tuple, size:int, color:tuple):
    font = pygame.font.Font(pygame.font.get_default_font(), size)
    surf = font.render(f"{text}", True, (color[0], color[1], color[2]))
    display.blit(surf, (pos[0], pos[1]))


class PG_Widnow_UI:
    def __init__(self, width, height):
        pygame.init()
        self.widht = width
        self.height = height
        self.window = pygame.display.set_mode((width, height))

    def update(self):
        pygame.display.flip()

    def clear(self, r, g, b):
        self.window.fill((r, g, b))

    def close(self):
        pygame.quit()
        _exit()


windowWidth = 1000
windowHeight = 150
pg_window = PG_Widnow_UI(windowWidth, windowHeight)

while True:
    
    pg_window.clear(255, 255, 255)

    events = pygame.event.get()
    handleEvents(events)

    pygame.joystick.init()

    write(pg_window.window, f"number of controller: {pygame.joystick.get_count()}", (0, 0), 15, (51, 51, 51))

    pg_window.update()