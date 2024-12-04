import sys
import pygame
from pygame.locals import QUIT
import random

# self file
from function import *
from object import *

"""GLOBAL VARIABLES"""

FPS = 120

# mouse button
LEFT = 1
RIGHT = 3

# the width and height of mouse icon 
MOUSEWIDTH = 72
MOUSEHEIGHT = 72

# clock
main_clock = pygame.time.Clock()

"""GLOBAL VARIABLES"""


# Loading page
def Loading_Page():
    # font
    start_font = pygame.font.SysFont(None, 60)

    # global variables
    global WINDOW_WIDTH, WINDOW_HEIGHT

    # local variables
    start_color = 255           # font color
    start_color_detect = True   # color changing
    
    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    return
            elif event.type == pygame.VIDEORESIZE:
                WINDOW_WIDTH, WINDOW_HEIGHT = window_surface.get_size()



        # color changing
        if start_color_detect == True:
            start_color -= 2
            if start_color < 100:
                start_color_detect = False
        else:
            start_color += 2
            if start_color >= 255:
                start_color_detect = True
        
        # text surface
        start_text_surface = start_font.render("Press space to start CRIME MANAGER!", True, (start_color, start_color, start_color))

        # draw
        window_surface.fill(BLACK)
        window_surface.blit(start_text_surface, (100, WINDOW_HEIGHT/2))

        # update
        pygame.display.update()
        main_clock.tick(FPS)



# Crime Manager
def Crime_Manager():

    # global variable
    global WINDOW_WIDTH, WINDOW_HEIGHT
    
    # local setting
    dropDownMenuLocation = (100, 100)               # drop down menu location
    selectionType = ["Name", "Time", "Crime Type"]  # option of drop down menu
    inputBoxLocation = (100, 400)                   # input box location

    # local variables
    isMenuOpen = False
    

    # build drop down menu
    dropDownMenu = Button(dropDownMenuLocation[0], dropDownMenuLocation[1], 200, 50, "Search Type", BLUE, "Tightones.otf", 35, WHITE)
    selection = pygame.sprite.Group()
    for i in range(3):
        selection.add(Button(dropDownMenuLocation[0], dropDownMenuLocation[1] + 50 * i + 50, 200, 50, selectionType[i], PURPLE, "Tightones.otf", 30, WHITE))

    # input box
    inputBox = InputBox(inputBoxLocation[0], inputBoxLocation[1], 500, 40, WHITE, 21, BLACK)

    # menu loop
    while True:
        # event detect
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            
            elif event.type == pygame.KEYDOWN:                                          # 鍵盤 
                if event.key == pygame.K_ESCAPE:                                        # 這裡可以嘗試做按下倒退鍵時持續刪除
                    return
                # Check for backspace
                elif event.key == pygame.K_BACKSPACE: 
                    inputBox.text = inputBox.text[:-1]

                # Unicode standard is used for string formation 
                else:
                    inputBox.text += event.unicode
            
            elif event.type == pygame.VIDEORESIZE:                                      # 改變視窗大小
                WINDOW_WIDTH, WINDOW_HEIGHT = window_surface.get_size()
            
            elif dropDownMenu.rect.collidepoint(pygame.mouse.get_pos()) or isMenuOpen:  # 下拉式選單
                if event.type == pygame.MOUSEBUTTONDOWN:
                    if event.button == LEFT:
                        if dropDownMenu.rect.collidepoint(event.pos):   # 檢查滑鼠是否在按鈕上
                            isMenuOpen = not isMenuOpen                     # 開啟或關閉下拉選單 
                                          
                        elif isMenuOpen:
                            for option in selection:                    # 檢查滑鼠是否在某個選項上
                                if option.rect.collidepoint(event.pos):
                                    dropDownMenu.set_text(option.text)

                            # close the drop down menu no matter where the mouse is
                            isMenuOpen = False
                
                # change the color of drop down menu
                elif  dropDownMenu.get_color() == BLUE:
                    dropDownMenu.set_color(LIGHT_BLUE)
                    dropDownMenu.set_text_color(BLACK)
            elif event.type == pygame.MOUSEBUTTONDOWN:
                inputBox.handle_event(event)
            else:
                dropDownMenu.set_color(BLUE)
                dropDownMenu.set_text_color(WHITE)
            
        
        
        if isMenuOpen:
            for option in selection:
                if option.rect.collidepoint(pygame.mouse.get_pos()):
                    option.set_color(LIGHT_PURPLE)
                    option.set_text_color(BLACK)
                else:
                    option.set_color(PURPLE)
                    option.set_text_color(WHITE)

        if inputBox.is_active():
            inputBox.set_color(InputBox.COLOR_ACTIVE)
        else:
            inputBox.set_color(InputBox.COLOR_PASSIVE)

        # draw
        window_surface.fill(BLACK)

        dropDownMenu.draw(window_surface)
        if isMenuOpen:
            for option in selection:
                option.draw(window_surface)
        
        inputBox.draw(window_surface)
        
        
        # update
        pygame.display.update()
        inputBox.update()
                

        main_clock.tick(FPS)

def main():

    # Waiting for the system getting ready.
    pygame.time.delay(500)

    Loading_Page()

    Crime_Manager()

if __name__ == '__main__':    
    main()