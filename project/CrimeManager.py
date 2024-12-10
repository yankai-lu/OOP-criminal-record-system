import sys
import pygame
from pygame.locals import QUIT
import random

# self file
from function import *
from object import *
from addpage import *
from deletepage import *
from searchpage import *

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
    dropDownMenuLocation = (400, 100)               # drop down menu location
    selectionType = ["Name", "Time", "Crime Type"]  # option of drop down menu
    inputBoxLocation = (400, 600)                   # input box location
    tableHight = 450                                # table height

    # local variables
    isMenuOpen = False
    
    # buttons
    table = Table(100, WINDOW_HEIGHT // 2 - tableHight // 2, 300, tableHight, "image\\table.png")
    add =       Button(table.rect.left + 24, table.rect.top + 100, 253, 50, "New Criminal", BLUE, "font\\calibri-regular.ttf", 35, WHITE)
    delete =    Button(table.rect.left + 24, table.rect.top + 200, 253, 50, "Delete", BLUE, "font\\calibri-regular.ttf", 35, WHITE)
    search =    Button(table.rect.left + 24, table.rect.top + 300, 253, 50, "Search", BLUE, "font\\calibri-regular.ttf", 35, WHITE)
    '''
    add = Button(100, 200, 40, 40, "+", BLUE, None, 40, WHITE)
    delete = Button(100, 300, 40, 40, "🗑️", BLUE, "font\\Segoe UI Emoji.ttf", 25, WHITE)
    search = Button(100, 500, 40, 40, "🔍", BLUE, "font\\Segoe UI Emoji.ttf", 25, WHITE)
    '''
    # build drop down menu
    dropDownMenu = Button(dropDownMenuLocation[0], dropDownMenuLocation[1], 200, 50, "Search Type", BLUE, "font\\Tightones.otf", 35, WHITE)
    selection = pygame.sprite.Group()
    for i in range(3):
        selection.add(Button(dropDownMenuLocation[0], dropDownMenuLocation[1] + 50 * i + 50, 200, 50, selectionType[i], PURPLE, "font\\Tightones.otf", 30, WHITE))

    # input box
    inputBox = InputBox(inputBoxLocation[0], inputBoxLocation[1], 500, 40, WHITE, 21, BLACK, "( Click here to type word )")

    
    # menu loop
    while True:
        # event detect
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            # 鍵盤 
            elif event.type == pygame.KEYDOWN:              
                if event.key == pygame.K_ESCAPE:            # (這裡可以嘗試做按下倒退鍵時持續刪除)
                    return
                # Check for backspace
                elif event.key == pygame.K_BACKSPACE: 
                    inputBox.text = inputBox.text[:-1]
                elif event.key == pygame.K_RETURN:          # 按下Enter鍵時，將輸入的字串傳送給後端
                    pass
                # Unicode standard is used for string formation 
                else:
                    inputBox.text += event.unicode
            # 改變視窗大小
            elif event.type == pygame.VIDEORESIZE:
                WINDOW_WIDTH, WINDOW_HEIGHT = window_surface.get_size()

            # mouse click event
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == LEFT:
                    if dropDownMenu.rect.collidepoint(event.pos):   # 檢查滑鼠是否在按鈕上
                        isMenuOpen = not isMenuOpen                 # 開啟或關閉下拉選單              
                    elif inputBox.handle_mouse_event(event):
                        pass
                    elif add.rect.collidepoint(event.pos):          # add new criminal
                        Add_Criminal_Page()
                    elif delete.rect.collidepoint(event.pos):       # delete criminal
                        Delete_Page()
                    elif search.rect.collidepoint(event.pos):       # search criminal
                        Search_Page()
                        # 需要return
                    elif isMenuOpen:
                        for option in selection:                    # 檢查滑鼠是否在某個選項上
                            if option.rect.collidepoint(event.pos):
                                dropDownMenu.set_text(option.text)
                        # close the drop down menu no matter where the mouse is
                        isMenuOpen = False
        
        # mouse hover event
        pos = pygame.mouse.get_pos()
        
        if isMenuOpen:
            dropDownMenu.set_color(LIGHT_BLUE)
            dropDownMenu.set_text_color(BLACK)
            for option in selection:
                if option.rect.collidepoint(pygame.mouse.get_pos()):
                    option.set_color(LIGHT_PURPLE)
                    option.set_text_color(BLACK)
                else:
                    option.set_color(PURPLE)
                    option.set_text_color(WHITE)
        elif dropDownMenu.rect.collidepoint(pos):
            dropDownMenu.set_color(LIGHT_BLUE)
            dropDownMenu.set_text_color(BLACK)
        elif add.rect.collidepoint(pos):
            add.set_color(LIGHT_BLUE)
            add.set_text_color(BLACK)
        elif delete.rect.collidepoint(pos):
            delete.set_color(LIGHT_BLUE)
            delete.set_text_color(BLACK)
        elif search.rect.collidepoint(pos):
            search.set_color(LIGHT_BLUE)
            search.set_text_color(BLACK)
        else:
            dropDownMenu.set_color(BLUE)
            dropDownMenu.set_text_color(WHITE)
            add.set_color(BLUE)
            add.set_text_color(WHITE)
            delete.set_color(BLUE)
            delete.set_text_color(WHITE)
            search.set_color(BLUE)
            search.set_text_color(WHITE)

        # input box color
        if inputBox.is_active():
            inputBox.set_color(InputBox.COLOR_ACTIVE)
        else:
            inputBox.set_color(InputBox.COLOR_PASSIVE)

        # draw
        window_surface.fill(BLACK)
        table.draw(window_surface)

        dropDownMenu.draw(window_surface)
        if isMenuOpen:
            for option in selection:
                option.draw(window_surface)
        
        inputBox.draw(window_surface)
        add.draw(window_surface)
        delete.draw(window_surface)
        search.draw(window_surface)

        # update
        pygame.display.update()
        inputBox.update()
                

        main_clock.tick(FPS)

# Add Criminal Page
def Add_Criminal_Page():
    # global variable
    global WINDOW_WIDTH, WINDOW_HEIGHT

    # local variables
    addPage = AddPage()
    addPage.open_page()

    while True:
        # event detect
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            # 鍵盤 
            elif event.type == pygame.KEYDOWN:              
                if event.key == pygame.K_ESCAPE:
                    addPage.close_page()
                    return
               
                if addPage.active_input_box is None:
                    pass
                elif event.key == pygame.K_RETURN:          # 按下Enter鍵時，將輸入的字串傳送給後端
                    SYSTEM.newCriminal(addPage.crime.text.encode('utf-8'), addPage.description.text.encode('utf-8'), int(addPage.year.text), int(addPage.month.text), int(addPage.day.text), int(addPage.hour.text), int(addPage.minute.text), addPage.ID.text.encode('utf-8'), addPage.birthday.text.encode('utf-8'), addPage.gender.text.encode('utf-8'), addPage.location.text.encode('utf-8'), addPage.name.text.encode('utf-8'))
                    print("Successdul add a new criminal.")
                elif event.key == pygame.K_BACKSPACE:        # Check for backspace
                    addPage.active_input_box.text = addPage.active_input_box.text[:-1]
                elif event.key == pygame.K_RETURN:          # 按下Enter鍵時，將輸入的字串傳送給後端
                    pass
                # Unicode standard is used for string formation 
                else:
                    addPage.active_input_box.text += event.unicode
            # 改變視窗大小
            elif event.type == pygame.VIDEORESIZE:
                WINDOW_WIDTH, WINDOW_HEIGHT = window_surface.get_size()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == LEFT:
                    if addPage.close.rect.collidepoint(event.pos):
                        addPage.close_page()
                        return
                    else:
                        addPage.handle_mouse_event(event)

        addPage.handle_mouse_hover(pygame.mouse.get_pos())

        for inputbox in addPage.inputBoxGroup:
            if inputbox.is_active():
                inputbox.set_color(InputBox.COLOR_ACTIVE)
            else:
                inputbox.set_color(InputBox.COLOR_PASSIVE)

        # draw
        addPage.draw(window_surface)

        # update
        pygame.display.update()
        addPage.update()
                
        main_clock.tick(FPS)


def Delete_Page():
    # global variable
    global WINDOW_WIDTH, WINDOW_HEIGHT

    # local variables
    deletePage = DeletePage()
    deletePage.open_page()

    while True:
        # event detect
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            # 鍵盤 
            elif event.type == pygame.KEYDOWN:              
                if event.key == pygame.K_ESCAPE:
                    deletePage.close_page()
                    return
                
                if deletePage.active_input_box is None:
                    pass
                elif event.key == pygame.K_RETURN:          # 按下Enter鍵時，將輸入的字串傳送給後端
                    SYSTEM.deleteCriminal(deletePage.name.text.encode('utf-8'), int(deletePage.year), int(deletePage.month), int(deletePage.day), int(deletePage.hour), int(deletePage.minute))
                    print("Successdul delete a criminal.")
                elif event.key == pygame.K_BACKSPACE:       # Check for backspace
                    deletePage.active_input_box.text = deletePage.active_input_box.text[:-1]
                elif event.key == pygame.K_RETURN:          # 按下Enter鍵時，將輸入的字串傳送給後端
                    pass
                # Unicode standard is used for string formation 
                else:
                    deletePage.active_input_box.text += event.unicode
            # 改變視窗大小
            elif event.type == pygame.VIDEORESIZE:
                WINDOW_WIDTH, WINDOW_HEIGHT = window_surface.get_size()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == LEFT:
                    if deletePage.close.rect.collidepoint(event.pos):
                        deletePage.close_page()
                        return
                    else:
                        deletePage.handle_mouse_event(event)


        for inputbox in deletePage.inputBoxGroup:
            if inputbox.is_active():
                inputbox.set_color(InputBox.COLOR_ACTIVE)
            else:
                inputbox.set_color(InputBox.COLOR_PASSIVE)

        # draw
        deletePage.draw(window_surface)

        # update
        pygame.display.update()
        deletePage.update()
                
        main_clock.tick(FPS)

def Search_Page():
     # global variable
    global WINDOW_WIDTH, WINDOW_HEIGHT

    # local variables
    searchPage = SearchPage()
    searchPage.open_page()

    while True:
        # event detect
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            # 鍵盤 
            elif event.type == pygame.KEYDOWN:              
                if event.key == pygame.K_ESCAPE:
                    searchPage.close_page()
                    return
               
                if searchPage.active_input_box is None:
                    pass
                elif event.key == pygame.K_RETURN:          # 按下Enter鍵時，將輸入的字串傳送給後端
                    print("Successdul searching.")
                elif event.key == pygame.K_BACKSPACE:        # Check for backspace
                    searchPage.active_input_box.text = searchPage.active_input_box.text[:-1]
                elif event.key == pygame.K_RETURN:          # 按下Enter鍵時，將輸入的字串傳送給後端
                    pass
                # Unicode standard is used for string formation 
                else:
                    searchPage.active_input_box.text += event.unicode
            # 改變視窗大小
            elif event.type == pygame.VIDEORESIZE:
                WINDOW_WIDTH, WINDOW_HEIGHT = window_surface.get_size()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == LEFT:
                    if searchPage.close.rect.collidepoint(event.pos):
                        searchPage.close_page()
                        return
                    else:
                        searchPage.handle_mouse_event(event)

        searchPage.handle_mouse_hover(pygame.mouse.get_pos())

        for inputbox in searchPage.inputBoxGroup:
            if inputbox.is_active():
                inputbox.set_color(InputBox.COLOR_ACTIVE)
            else:
                inputbox.set_color(InputBox.COLOR_PASSIVE)

        # draw
        searchPage.draw(window_surface)

        # update
        pygame.display.update()
        searchPage.update()
                
        main_clock.tick(FPS)

def main():
    # Waiting for the system getting ready.
    pygame.time.delay(500)

    Loading_Page()

    Crime_Manager()

if __name__ == '__main__':    
    main()