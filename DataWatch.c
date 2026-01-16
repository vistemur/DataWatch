#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct player {
    int id;
    char* nickName;
    int maxRating;
    int currentRating;
    int role;
    int captain;
} typedef player;


struct data {
    char* name;
    int playersAmount;
    int rating;
    struct player* players;
} typedef data;


struct Team {
    int teamId;
    struct data data;
    struct Team* next;
    struct Team* previous;
} typedef Team;


struct Head {
    struct Team* first;
    struct Team* current;
    struct Team* last;
    int amount;
} typedef Head;


struct Head* initHead(struct Head *head) {
    head = (struct Head*)malloc(1 * sizeof(struct Head));
    head->amount = 0;
    head->current = NULL;
    head->first = NULL;
    return head;
}

struct Head* sortTeamsByRating(struct Head* head);

struct Head* addTeam(struct data data, struct Head *head) {
    
    struct Team *element;
    element = (struct Team*)malloc(1 * sizeof(struct Team));
    
    element->teamId = head->amount;
    element->data = data;
    head->amount = head->amount + 1;
    
    if (element->teamId == 0) {
        head->first = element;
        head->last = element;
    } else {
        element->previous = head->last;
        head->last->next = element;
        head->last = element;
    }
    
    return head;
}


struct Head* giveIds(struct Head* head) {
    
    int counter = 0;
    
    if (head->amount != 0) {
        head->current = head->first;
        head->current->teamId = counter;
        
        for (counter = 1; counter < head->amount; counter++) {
            head->current = head->current->next;
            head->current->teamId = counter;
        }
        
    }
    
    return head;
}


unsigned long printString (char* word) {
    
    int counter;
    
    for (counter = 0; counter < strlen(word); counter++) {
        printf("%c", word[counter]);
    }
    
    return strlen(word);
}


int printStringWithEnd (char* word) {
    
    int counter;
    
    for (counter = 0; word[counter] != '\0'; counter++) {
        printf("%c", word[counter]);
    }
    
    return counter;
}


char* deleteSpacesFromWordEnd(char* word) {
    
    unsigned long counter;
    
    for (counter = strlen(word) - 1; word[counter] != ' '; counter--) {
        word[counter] = '\0';
    }
    
    return word;
}


struct Head* addTeamAtPosition(struct Head *head, int position, struct data data) {
    
    if (position > -1 && position < head->amount) {
        
        int counter;
        struct Team* element;
        element = (struct Team*)malloc(1 * sizeof(struct Team));
        element->data = data;
        
        if (position == 0) {
            element->next = head->first;
            head->first->previous = element;
            head->first = element;
        } else {
            head->current = head->first;
            for (counter = 0; counter < head->amount; counter++) {
                if (counter == position - 1) {
                    element->next = head->current->next;
                    element->previous = head->current;
                    head->current->next = element;
                } else {
                    head->current = head->current->next;
                }
            }
        }
        head->amount++;
        head = giveIds(head);
    } else {
        if (position == head->amount) {
            head = addTeam(data, head);
        }
    }
    
    return head;
}


void printPlayer(struct player* player) {
    
    int counter;
    
    printf("| ");
    for (counter = 15 - printStringWithEnd(player->nickName); counter > 0; counter--) {
        printf(" ");
    }
    printf("| ");
    printf("%4d | %4d |", player->maxRating, player->currentRating);
    switch (player->role) {
        case 2:
            printf(" dps  |\n");
            break;
        case 3:
            printf(" tank |\n");
            break;
        case 4:
            printf(" flex |\n");
            break;
        default:
            printf(" heal |\n");
            break;
    }
    printf("+----------------+------+------+------+\n");
}


void printTeam(struct Team* team) {
    
    int counter;
    
    printf("Team name: ");
    printString(team->data.name);
    printf("\n");
    printf("Team rating: ");
    printf("%d", team->data.rating);
    printf("\n");
    printf("Team id: ");
    printf("%d", team->teamId);
    printf("\n");
    printf("+----------------+------+------+------+\n");
    printf("|    nickname    | max  | cur  | role |\n");
    printf("+----------------+------+------+------+\n");
    for (counter = 0; counter < team->data.playersAmount; counter++) {
        printPlayer(&team->data.players[counter]);
    }
    printf("\n\n");
}


void printAllTeams(struct Head* head) {
    int counter = 0;
    printf("\n\n");
    head->current = head->first;
    for (counter = 0; counter < head->amount; counter++) {
        printTeam(head->current);
        if (head->current->teamId < head->amount - 1) {
            head->current = head->current->next;
        }
    }
}


int toInt(char* a, int size) {
    
    int c, sign = 0, offset, n;
    
    if (a[0] == '-') {
        sign = -1;
    }
    
    if (sign == -1) {
        offset = 1;
    }
    else {
        offset = 0;
    }
    
    n = 0;
    
    for (c = offset;c < size; c++) {
        n = n * 10 + a[c] - '0';
    }
    
    if (sign == -1) {
        n = -n;
    }
    
    return n;
}


char* pastux(char* path, char *string) {
    string = NULL;
    FILE* File = fopen(path, "r");
    
    if (File) {
        fseek(File, 0, SEEK_END);
        long int length = ftell(File);
        rewind(File);
        string = (char*) malloc(sizeof(char) * (length + 1));
        if (string) {
            fread(string, sizeof(char), length, File);
            string[length] = 0;
        }
        
        fclose(File);
        string[length + 1] = '\0';
    }
    return string;
}


char** initializeDoubleArray(char *string, char **c) {
    
    int useless, amount, stolb, len;
    
    len = 1;
    stolb = 0;
    amount = 1;
    
    for (useless = 0; string[useless] != '\0'; useless++) {
        if (string[useless] == '\n') {
            amount++;
        }
    }
    
    c = (char**)malloc(amount * sizeof(char*));
    
    for (useless = 0;string[useless] != '\0'; useless++) {
        if (string[useless] == '\n') {
            c[stolb] = (char*)malloc(len * sizeof(char));
            stolb++;
            len = 1;
        } else {
            len++;
        }
    }
    
    c[stolb] = (char*)malloc(1 * sizeof(char));
    
    return c;
}


int doubleArrayFromSingle(char *string, char **c) {
    
    int k = 0;
    int uselesss = 0;
    int useless;
    
    for (useless = 0; string[useless] != '\0'; useless++) {
        c[k][uselesss] = string[useless];
        if (string[useless] == '\n') {
            uselesss = -1;
            k++;
        }
        uselesss++;
    }
    return k;
}


char* spaceX(char* word,int amount) {
    
    int counter;
    
    for (counter = 0; counter < amount; counter++) {
        word[counter] = ' ';
    }
    
    return word;
}


char* fillWord(char* word, int amount, char sumbol) {
    
    int counter;
    
    for (counter = 0; counter < amount; counter++) {
        word[counter] = sumbol;
    }
    
    return word;
}


void clearString (char* string) {
    
    int counter;
    
    for (counter = 0; counter < strlen(string); counter++) {
        string[counter] = '\0';
    }
    
}

struct Head* deleteTeamWithId(struct Head* head, int element);

struct Head* sortTeamsByRating(struct Head* head) {
    
    struct Team *replacer = (struct Team*)malloc(1 * sizeof(struct Team));
    
    for (int counter = 0; counter < head->amount - 1; counter++) {
        for (head->current = head->first; head->current->teamId < head->amount - 1; head->current = head->current->next) {
            if (head->current->data.rating < head->current->next->data.rating) {
                replacer = head->current;
                head = addTeamAtPosition(head, replacer->teamId, replacer->next->data);
                head = deleteTeamWithId(head, replacer->teamId + 1);
                head->current = head->first;
            }
        }
    }
    
    free(replacer);
    head = giveIds(head);
    
    return head;
}


struct Head* zabivaka(char ** c, struct Head* head,int sizey) {
    
    int counter1, counter2, counter3, counter4;
    char *string;
    struct data* data = (struct data*)malloc(sizey * sizeof(struct data));
    string = (char*)malloc(100 * sizeof(char));
        
    for (counter1 = 0; counter1 < sizey; counter1++) {
        data[counter1].name = (char*)malloc(100 * sizeof(char));
        data[counter1].name = spaceX(data[counter1].name, 50);
        
        for (counter2 = 0; c[counter1][counter2] != ';'; counter2++) {
            if (c[counter1][counter2] != '\0') {
                data[counter1].name[counter2] = c[counter1][counter2];
            }
        }
        data[counter1].name[counter2] ='\0';
        counter2++;
        
        for (counter3 = 0;c[counter1][counter2 + counter3] != '{'; counter3++) {
            string[counter3] = c[counter1][counter2 + counter3];
        }
        data[counter1].rating = toInt(string, counter3);
        clearString(string);
        counter2 = counter2 + counter3 + 1;
        
        data[counter1].players = (struct player*)malloc(100 * sizeof(struct player));
        counter4 = 0;
        
        while (c[counter1][counter2] != '}') {
            
            data[counter1].players[counter4].nickName = (char*)malloc(100 * sizeof(char));
            data[counter1].players[counter4].nickName = spaceX(data[counter1].players[counter4].nickName, 50);
            
            for (counter3 = 0; c[counter1][counter2 + counter3] != ';'; counter3++) {
                if (c[counter1][counter2 + counter3] != '\0') {
                    data[counter1].players[counter4].nickName[counter3] = c[counter1][counter2 + counter3];
                }
            }
            data[counter1].players[counter4].nickName[counter3] = '\0';
            counter2 = counter2 + counter3 + 1;
            
            for (counter3 = 0;c[counter1][counter2 + counter3] != ';'; counter3++) {
                string[counter3] = c[counter1][counter2 + counter3];
            }
            data[counter1].players[counter4].maxRating = toInt(string, counter3);
            clearString(string);
            counter2 = counter2 + counter3 + 1;
            
            for (counter3 = 0;c[counter1][counter2 + counter3] != ';'; counter3++) {
                string[counter3] = c[counter1][counter2 + counter3];
            }
            data[counter1].players[counter4].currentRating = toInt(string, counter3);
            clearString(string);
            counter2 = counter2 + counter3 + 1;
            
            for (counter3 = 0;c[counter1][counter2 + counter3] != ';'; counter3++) {
                string[counter3] = c[counter1][counter2 + counter3];
            }
            data[counter1].players[counter4].role = toInt(string, counter3);
            clearString(string);
            counter2 = counter2 + counter3 + 1;
            
            for (counter3 = 0;c[counter1][counter2 + counter3] != ';'; counter3++) {
                string[counter3] = c[counter1][counter2 + counter3];
            }
            data[counter1].players[counter4].captain = toInt(string, counter3);
            clearString(string);
            counter2 = counter2 + counter3 + 1;
            
            data[counter1].players[counter4].id = counter4;
            
            counter4++;
        }
        
        data[counter1].playersAmount = counter4;
        head = addTeam(data[counter1], head);
    }
    
    return head;
}


struct Head* deleteFirstElement(struct Head *head) {
    
    if (head->amount != 0) {
        if (head->amount == 1) {
            head->first = NULL;
            head->last = NULL;
            head->amount--;
        } else {
            head->first->next->previous = NULL;
            head->first = head->first->next;
            head->amount--;
            head = giveIds(head);
        }
    } else {
        printf("nothing to delete :(\n");
    }
    
    return head;
}


struct Head* deleteLastElement(struct Head *head) {
    
    int counter;
    
    if (head->amount != 0) {
        if (head->amount == 1) {
            head->first = NULL;
            head->last = NULL;
            head->amount--;
        } else {
            if (head->amount == 2) {
                head->first->next = NULL;
                head->last = head->first;
                head->amount--;
            } else {
                head->current = head->first;
                for (counter = 0; counter < head->amount - 2; counter++) {
                    head->current = head->current->next;
                }
                head->current->next = NULL;
                head->last = head->current;
                head->amount--;
            }
        }
    } else {
        printf("nothing to delete :(\n");
    }
    
    return head;
}


struct Head* deleteTeamWithId(struct Head* head, int element) {
    
    int counter;
    
    if (element > -1 && element < head->amount) {
        if (head->amount != 0) {
            if (element == 0) {
                head = deleteFirstElement(head);
            } else {
                if (element == head->amount - 1) {
                    head = deleteLastElement(head);
                } else {
                    head->current = head->first;
                    for (counter = 0; counter < head->amount; counter++) {
                        if (counter == element - 1) {
                            head->current->next = head->current->next->next;
                            head->current->next->previous = head->current;
                        } else {
                            head->current = head->current->next;
                        }
                    }
                    head->amount--;
                    head = giveIds(head);
                }
            }
        } else {
            printf("nothing to delete :(\n");
        }
    } else {
        printf("element %d is out of range", element);
    }
    
    return head;
}


int similarWords(char* word1, char* word2) {
    
    int sameSumbols = 0, counter2, answer = 0;
    
    for (counter2 = 0; counter2 < strlen(word1); counter2++) {
        if (word1[counter2] == word2[counter2]) {
            sameSumbols++;
        }
    }
    
    if (sameSumbols == strlen(word1) || word1 == word2) {
        answer = 1;
    }
    
    return answer;
}


struct Head* deleteTeamWithName(struct Head* head, char* name) {
    
    int counter, deleting = 0;
    
    if (head->amount != 0) {
        if (similarWords(name, head->first->data.name) == 1) {
            printf("\nteam ");
            printString(head->first->data.name);
            puts(" has been deleted");
            head = deleteFirstElement(head);
        } else {
            if (similarWords(name, head->last->data.name) == 1) {
                printf("\nteam ");
                printString(head->last->data.name);
                puts(" has been deleted");
                head = deleteLastElement(head);
            } else {
                head->current = head->first;
                for (counter = 0; counter < head->amount; counter++) {
                    if (similarWords(name, head->current->data.name) == 1) {
                        head->current->previous->next = head->current->next;
                        head->current->next->previous = head->current->previous;
                        printf("\nteam ");
                        printString(head->current->data.name);
                        puts(" has been deleted");
                        deleting = 1;
                        counter = head->amount;
                    } else {
                        head->current = head->current->next;
                    }
                }
                
                if (deleting == 1) {
                    head->amount--;
                    head = giveIds(head);
                } else {
                    printf("no element comparable with ");
                    printString(name);
                    printf("\n");
                }
                
            }
        }
    } else {
        printf("no teams to delete");
    }
    
    return head;
}


char* enterUserWord(char *userWord) {
    
    int counter;
    
    scanf(" %c", &userWord[0]);
    for (counter = 1; userWord[counter - 1] != '\n'; counter++) {
        userWord[counter] = getchar();
    }
    
    userWord[strlen(userWord) - 1] = '\0';
    
    return userWord;
}


struct Head* deleteTeamMenuxa (struct Head* head) {
    
    int answer, id;
    char* name;
    name = (char*)malloc(100 * sizeof(char));
    
    puts("\nenter delete option:");
    puts("1 - delete with id");
    puts("2 - delete with name");
    printf("option: ");
    scanf("%d", &answer);
    
    switch (answer) {
        case 1:
            printf("enter team id: ");
            scanf("%d", &id);
            head = deleteTeamWithId(head, id);
            break;
        case 2:
            printf("enter team name: ");
            name = enterUserWord(name);
            head = deleteTeamWithName(head, name);
            break;
        default:
            break;
    }
    free(name);
    
    
    return head;
}

struct Team* sortPlayersByRating(struct Team* team);

struct Team* changeTeamRating(struct Team* team) {
    
    int rating = 0, counter;
    
    for (counter = 0; counter < team->data.playersAmount; counter++) {
        rating = rating + team->data.players[counter].currentRating;
    }
    team->data.rating = rating / counter;
    
    return team;
}

struct Head* addTeamMenu(struct Head* head) {
    
    struct data dt;
    int answer = 1;
    dt.name = (char*)malloc(100 * sizeof(char));
    dt.players = (struct player*)malloc(100 * sizeof(struct player));
    dt.players[0].nickName = (char*)malloc(100 * sizeof(char));
    
    printf("\n\nenter team's name: ");
    dt.name = enterUserWord(dt.name);
    printf("add leader...\n");
    printf("leader nickname: ");
    dt.players[0].nickName = enterUserWord(dt.players[0].nickName);
    dt.players[0].captain = 1;
    printf("leader current rating = ");
    scanf("%d", &dt.players[0].currentRating);
    printf("leader max rating = ");
    scanf("%d", &dt.players[0].maxRating);
    dt.players[0].id = 0;
    printf("leader role (1 - healer, 2 - dps, 3 - tank, 4 - flex): ");
    scanf("%d", &dt.players[0].role);
    dt.playersAmount = 1;
    printf("add player? (1 - yes, 2 - no)\n");
    scanf("%d", &answer);
    while (answer == 1) {
        dt.players[dt.playersAmount].nickName = (char*)malloc(100 * sizeof(char));
        printf("player %d nickname: ", dt.playersAmount);
        dt.players[dt.playersAmount].nickName = enterUserWord(dt.players[dt.playersAmount].nickName);
        dt.players[dt.playersAmount].captain = 0;
        printf("player %d current rating = ", dt.playersAmount);
        scanf("%d", &dt.players[dt.playersAmount].currentRating);
        printf("player %d max rating = ", dt.playersAmount);
        scanf("%d", &dt.players[dt.playersAmount].maxRating);
        dt.players[dt.playersAmount].id = dt.playersAmount;
        printf("player %d role (1 - healer, 2 - dps, 3 - tank, 4 - flex): ", dt.playersAmount);
        scanf("%d", &dt.players[dt.playersAmount].role);
        dt.playersAmount++;
        printf("add another player? (1 - yes, 2 - no)\n");
        scanf("%d", &answer);
    }
    dt.rating = 0;
    for (answer = 0; answer < dt.playersAmount; answer++) {
        dt.rating = dt.rating + dt.players[answer].currentRating;
    }
    dt.rating = dt.rating / dt.playersAmount;
    
    head = addTeam(dt, head);
    head->last = sortPlayersByRating(head->last);
    head = sortTeamsByRating(head);
    
    return head;
}


struct Team* addPlayer(struct Team* team) {
    
    int counter;
    
    team->data.players[team->data.playersAmount].nickName = (char*)malloc(100 * sizeof(char));
    printf("player %d nickname: ", team->data.playersAmount);
    team->data.players[team->data.playersAmount].nickName = enterUserWord(team->data.players[team->data.playersAmount].nickName);
    team->data.players[team->data.playersAmount].captain = 0;
    printf("player %d current rating = ", team->data.playersAmount);
    scanf("%d", &team->data.players[team->data.playersAmount].currentRating);
    printf("player %d max rating = ", team->data.playersAmount);
    scanf("%d", &team->data.players[team->data.playersAmount].maxRating);
    team->data.players[team->data.playersAmount].id = team->data.playersAmount;
    printf("player %d role (1 - healer, 2 - dps, 3 - tank, 4 - flex): ", team->data.playersAmount);
    scanf("%d", &team->data.players[team->data.playersAmount].role);
    team->data.playersAmount++;
    team->data.rating = 0;
    for (counter = 0; counter < team->data.playersAmount; counter++) {
        team->data.rating = team->data.rating + team->data.players[counter].currentRating;
    }
    team->data.rating = team->data.rating / team->data.playersAmount;
    team = sortPlayersByRating(team);
    
    return team;
}


void printPlayersWithId(struct Team* team) {
    
    int counter, counter2;
    
    printf("\n\n");
    for (counter = 0; counter < team->data.playersAmount; counter++) {
        printString(team->data.players[counter].nickName);
        for (counter2 = 30; counter2 > strlen(team->data.players[counter].nickName); counter2--) {
            printf(" ");
        }
        printf(" - %d\n", team->data.players[counter].id);
    }
    printf("\n");
}


struct Team* givePlayerIds(struct Team* team) {
    
    int counter;
    
    for (counter = 0; counter < team->data.playersAmount; counter++) {
        team->data.players[counter].id = counter;
    }
    
    return team;
}


struct Team* deletePlayerWithId(struct Team* team, int id) {
    
    int counter;
    
    if (id > -1 && id < team->data.playersAmount) {
        if (team->data.players[id].captain != 1) {
            printf("\n");
            printString(team->data.players[id].nickName);
            printf(" has been deleted\n");
            for (counter = id; counter < team->data.playersAmount; counter++) {
                team->data.players[counter] = team->data.players[counter + 1];
            }
            team->data.playersAmount--;
            team = givePlayerIds(team);
        } else {
            printf("\nplayer %d is captain and can't be deleted\n", id);
        }
    } else {
        printf("\nno player with id %d\n", id);
    }
    
    return team;
}


struct Team* deletePlayerWithName(struct Team* team, char* name) {
    
    int counter;
    
    for (counter = 0; counter < team->data.playersAmount; counter++) {
        if (similarWords(name, team->data.players[counter].nickName) == 1) {
            team = deletePlayerWithId(team, counter);
            counter = team->data.playersAmount;
        }
    }
    
    return team;
}


struct Team* deletePlayerMenu(struct Team* team) {
    
    int answer, id;
    char* name;
    name = (char*)malloc(100 * sizeof(char));
    
    printf("\n\n");
    printTeam(team);
    puts("\nenter choose option:");
    puts("1 - delete player with id");
    puts("2 - delete player with nickname");
    puts("3 - back");
    printf("option: ");
    scanf("%d", &answer);
    
    switch (answer) {
        case 1:
            printPlayersWithId(team);
            printf("enter player id: ");
            scanf("%d", &id);
            team = deletePlayerWithId(team, id);
            break;
        case 2:
            printf("enter player name: ");
            name = enterUserWord(name);
            team = deletePlayerWithName(team, name);
            break;
        default:
            break;
    }
    free(name);
    
    return team;
}


struct Team* newLeaderWithId(struct Team* team, int id) {
    
    struct player player;
    
    if (id > -1 && id < team->data.playersAmount) {
        team->data.players[0].captain = 0;
        player = team->data.players[0];
        team->data.players[0] = team->data.players[id];
        team->data.players[0].captain = 1;
        team->data.players[id] = player;
        printf("\n");
        printString(team->data.players[0].nickName);
        printf(" is new leader\n");
        team = givePlayerIds(team);
        team = sortPlayersByRating(team);
    } else {
        printf("\nno player with id %d\n", id);
    }
    
    return team;
}


struct Team* newLeaderWithName(struct Team* team, char* name) {
    
    int counter;
    
    for (counter = 0; counter < team->data.playersAmount; counter++) {
        if (similarWords(name, team->data.players[counter].nickName) == 1) {
            team = newLeaderWithId(team, counter);
            counter = team->data.playersAmount;
        }
    }
    team = sortPlayersByRating(team);
    
    return team;
}


struct Team* leaderMenu(struct Team* team) {
    
    int answer, id;
    char* name;
    name = (char*)malloc(100 * sizeof(char));
    
    printf("\ncurrent leader - ");
    printString(team->data.players[0].nickName);
    
    puts("\n\nenter choose option:");
    puts("1 - choose new leader with id");
    puts("2 - choose new leader with nickname");
    puts("3 - back");
    printf("option: ");
    scanf("%d", &answer);
    
    switch (answer) {
        case 1:
            printPlayersWithId(team);
            printf("enter new leader id: ");
            scanf("%d", &id);
            team = newLeaderWithId(team, id);
            break;
        case 2:
            printf("enter new leader name: ");
            name = enterUserWord(name);
            team = newLeaderWithName(team, name);
            break;
        default:
            break;
    }
    free(name);
    
    return team;
}


struct Team* sortPlayersByRating(struct Team* team) {
    
    int counter, counter2;
    struct player replacer;
    
    for (counter = team->data.playersAmount - 1; counter > 0; counter--) {
        for (counter2 = 1; counter2 < counter; counter2++) {
            if (team->data.players[counter2].currentRating < team->data.players[counter2 + 1].currentRating) {
                replacer = team->data.players[counter2];
                team->data.players[counter2] = team->data.players[counter2 + 1];
                team->data.players[counter2 + 1] = replacer;
            }
        }
    }
    
    team = givePlayerIds(team);
    
    return  team;
}


int playerIdFromName(struct Team* team, char* name) {
    
    int counter, id = -1;
    
    for (counter = 0; counter < team->data.playersAmount; counter++) {
        if (similarWords(name, team->data.players[counter].nickName) == 1) {
            id = counter;
            counter = team->data.playersAmount;
        }
    }
    
    return id;
}


void printPlayerRole(struct player player) {
    
    switch (player.role) {
        case 2:
            printf("dps");
            break;
        case 3:
            printf("tank");
            break;
        case 4:
            printf("flex");
            break;
        default:
            printf("heal");
            break;
    }
    
}


void printPlayerData(struct player player) {
    printf("player %d nickname - ", player.id);
    printString(player.nickName);
    printf("\nplayer %d id - %d\n", player.id, player.id);
    printf("player %d current rating - %d\n", player.id, player.currentRating);
    printf("player %d maximum rating - %d\n", player.id, player.maxRating);
    printf("player %d role - ", player.id);
    printPlayerRole(player);
    if (player.captain == 1) {
        printf("\nplayer %d is captain", player.id);
    }
    printf("\n");
}

struct Team* teamMenu(struct Team* team);

struct Team* playerMenu(struct Team* team, int id) {
    
    int answer;
    char* word;
    word = (char*)malloc(100 * sizeof(char));
    
    if (id > -1 && id < team->data.playersAmount) {
        
        printf("\n\n");
        printPlayerData(team->data.players[id]);
        printf("\nenter choose option:\n");
        printf("1 - change player %d nickname\n", id);
        printf("2 - change player %d current rating\n", id);
        printf("3 - change player %d maximum rating\n", id);
        printf("4 - make player %d captain\n", id);
        printf("5 - delete player %d\n", id);
        puts("6 - back");
        printf("option: ");
        scanf("%d", &answer);
        
        switch (answer) {
            case 1:
                printf("player %d current nickname - ", id);
                printString(team->data.players[id].nickName);
                printf("\nenter new nickname: ");
                team->data.players[id].nickName = enterUserWord(team->data.players[id].nickName);
                team = playerMenu(team, id);
                break;
            case 2:
                printf("player %d current rating - %d\n", id, team->data.players[id].currentRating);
                printf("enter new current rating: ");
                scanf("%d", &team->data.players[id].currentRating);
                team = playerMenu(team, id);
                break;
            case 3:
                printf("player %d maximum rating - %d\n", id, team->data.players[id].maxRating);
                printf("enter new maximum rating: ");
                scanf("%d", &team->data.players[id].maxRating);
                team = playerMenu(team, id);
                break;
            case 4:
                team = newLeaderWithId(team, id);
                team = playerMenu(team, id);
                break;
            case 5:
                team = deletePlayerWithId(team, id);
                team = teamMenu(team);
                break;
            default:
                break;
        }
        
    } else {
        printf("\nno player with id %d", id);
    }
    free(word);
    
    return team;
}


struct Team* choosePlayerMenu(struct Team* team) {
    
    int answer, id;
    char* name;
    name = (char*)malloc(100 * sizeof(char));
    
    printf("\n\n");
    printTeam(team);
    puts("\nenter choose option:");
    puts("1 - choose player with id");
    puts("2 - choose player with nickname");
    puts("3 - back");
    printf("option: ");
    scanf("%d", &answer);
    
    switch (answer) {
        case 1:
            printPlayersWithId(team);
            printf("enter player id: ");
            scanf("%d", &id);
            team = playerMenu(team, id);
            break;
        case 2:
            printf("enter player name: ");
            name = enterUserWord(name);
            id = playerIdFromName(team, name);
            team = playerMenu(team, id);
            break;
        default:
            break;
    }
    free(name);
    
    return team;
}


struct Team* teamMenu(struct Team* team) {
    
    int answer;
    char* name;
    name = (char*)malloc(100 * sizeof(char));
    
    printf("\n\n");
    printTeam(team);
    puts("\nenter choose option:");
    puts("1 - print team");
    puts("2 - add player");
    puts("3 - delete player");
    puts("4 - make new leader");
    puts("5 - change team name");
    puts("6 - choose player");
    puts("7 - back");
    printf("option: ");
    scanf("%d", &answer);
    
    switch (answer) {
        case 1:
            printf("\n\n");
            printTeam(team);
            team = teamMenu(team);
            break;
        case 2:
            team = addPlayer(team);
            team = teamMenu(team);
            break;
        case 3:
            team = deletePlayerMenu(team);
            team = teamMenu(team);
            break;
        case 4:
            team = leaderMenu(team);
            team = teamMenu(team);
            break;
        case 5:
            printf("\ncurrent team name - ");
            printString(team->data.name);
            printf("\nnew team name - ");
            name = enterUserWord(name);
            team->data.name = name;
            team = teamMenu(team);
            break;
        case 6:
            team = choosePlayerMenu(team);
            team = teamMenu(team);
            break;
        default:
            break;
    }
    free(name);
    
    return team;
}


struct Head* chooseTeamWithName(struct Head* head, char* name) {
    
    int counter, deleting = 0;
    
    if (head->amount != 0) {
        if (similarWords(name, head->first->data.name) == 1) {
            head->first = teamMenu(head->first);
        } else {
            if (similarWords(name, head->last->data.name) == 1) {
                head->last = teamMenu(head->last);
            } else {
                head->current = head->first;
                for (counter = 0; counter < head->amount; counter++) {
                    if (similarWords(name, head->current->data.name) == 1) {
                        head->current = teamMenu(head->current);
                    } else {
                        head->current = head->current->next;
                    }
                }
                
                if (deleting != 1) {
                    printf("no element comparable with ");
                    printString(name);
                    printf("\n");
                }
                
            }
        }
    } else {
        printf("no teams to delete");
    }
    
    return head;
}


struct Head* chooseTeamWithId(struct Head* head, int element) {
    
    int counter;
    
    if (element > -1 && element < head->amount) {
        if (head->amount != 0) {
            if (element == 0) {
                head->first = teamMenu(head->first);
            } else {
                if (element == head->amount - 1) {
                    head->last = teamMenu(head->last);
                } else {
                    head->current = head->first;
                    for (counter = 0; counter < head->amount; counter++) {
                        if (counter == element) {
                            head->current = teamMenu(head->current);
                        } else {
                            head->current = head->current->next;
                        }
                    }
                }
            }
        } else {
            printf("nothing to delete :(\n");
        }
    } else {
        printf("element %d is out of range", element);
    }
    
    return head;
}


struct Head* chooseTeamMenu(struct Head* head) {
    
    int answer, id;
    char* name;
    name = (char*)malloc(100 * sizeof(char));
    
    puts("\nenter choose option:");
    puts("1 - choose with id");
    puts("2 - choose with name");
    printf("option: ");
    scanf("%d", &answer);
    
    switch (answer) {
        case 1:
            printf("enter team id: ");
            scanf("%d", &id);
            head = chooseTeamWithId(head, id);
            break;
        case 2:
            printf("enter team name: ");
            name = enterUserWord(name);
            head = chooseTeamWithName(head, name);
            break;
        default:
            break;
    }
    free(name);
    
    return head;
}


struct Head* mainMenuxa (struct Head* head) {
    
    int answer;
    
    puts("\nenter option:");
    puts("1 - print all teams");
    puts("2 - add team");
    puts("3 - delete team");
    puts("4 - choose team");
    puts("5 - exit");
    printf("option: ");
    scanf("%d", &answer);
    
    switch (answer) {
        case 1:
            printAllTeams(head);
            head = mainMenuxa(head);
            break;
        case 2:
            head = addTeamMenu(head);
            head = sortTeamsByRating(head);
            head = mainMenuxa(head);
            break;
        case 3:
            head = deleteTeamMenuxa(head);
            head = mainMenuxa(head);
            break;
        case 4:
            head = chooseTeamMenu(head);
            head = mainMenuxa(head);
            break;
        default:
            break;
    }
    
    return head;
}


struct Head* sortirAllPlayers(struct Head* head) {
    
    for (head->current = head->first; head->current && head->current->teamId < head->amount - 1; head->current = head->current->next) {
        head->current = sortPlayersByRating(head->current);
        head->current = changeTeamRating(head->current);
    }
    
    if (head->current) {
        head->current = sortPlayersByRating(head->current);
        head->current = changeTeamRating(head->current);
    }
    
    return head;
}


char* mixer(char* string1, char* string2) {
    
    unsigned long counter1 = strlen(string1);
    int counter2;
    
    for (counter2 = 0; string2[counter2] != '\0'; counter2++) {
        string1[counter1] = string2[counter2];
        counter1++;
    }
    
    return string1;
}


char* mixerWithoutSpace(char* string1, char* string2) {
    
    unsigned long counter1 = strlen(string1);
    int counter2;
    
    for (counter2 = 0; string2[counter2] != '\0'; counter2++) {
        if (string2[counter2] != ' ') {
            string1[counter1] = string2[counter2];
            counter1++;
        }
    }
    
    return string1;
}



char* stringFromHead(struct Head* head,char* string) {
    
    int teamCounter, playerCounter;
    char* inter = (char*)malloc(5 * sizeof(char));
    
    head->current = head->first;
    for (teamCounter = 0; teamCounter < head->amount; teamCounter++) {
        string = mixerWithoutSpace(string, head->current->data.name);
        string[strlen(string)] = ';';
        sprintf(inter, "%d", head->current->data.rating);
        string = mixer(string, inter);
        string[strlen(string)] = ';';
        string[strlen(string)] = '{';
        for (playerCounter = 0; playerCounter < head->current->data.playersAmount; playerCounter++) {
            string = mixerWithoutSpace(string, head->current->data.players[playerCounter].nickName);
            string[strlen(string)] = ';';
            sprintf(inter, "%d", head->current->data.players[playerCounter].maxRating);
            string = mixer(string, inter);
            string[strlen(string)] = ';';
            sprintf(inter, "%d", head->current->data.players[playerCounter].currentRating);
            string = mixer(string, inter);
            string[strlen(string)] = ';';
            sprintf(inter, "%d", head->current->data.players[playerCounter].role);
            string = mixer(string, inter);
            string[strlen(string)] = ';';
            sprintf(inter, "%d", head->current->data.players[playerCounter].captain);
            string = mixer(string, inter);
            string[strlen(string)] = ';';
        }
        string[strlen(string)] = '}';
        string[strlen(string)] = '\n';
        head->current = head->current->next;
    }
    
    return string;
}


struct Head* save(struct Head* head, char* path) {
    
    char* string = (char*)malloc(1000000 * sizeof(char));
    
    string = stringFromHead(head, string);
    FILE* File = fopen(path, "w");
    
    if (File && string) {
        fprintf(File, string, 1);
    }
    fclose(File);
    
    return head;
}


int main() {
    
    struct Head* head = NULL;
    int sizey, counter;
    char *string;
    char **c;
    head = initHead(head);
    
    string = NULL;
    c = NULL;
    string = pastux("DataText.txt", string);
    
    if (string) {
        c = initializeDoubleArray(string, c);
        if (c) {
            sizey = doubleArrayFromSingle(string, c);
            head = zabivaka(c, head, sizey);
            head = giveIds(head);
            
            for (counter = 0; counter < sizey; counter++) {
                free(c[counter]);
            }
            free(c);
            free(string);
            
            head = sortirAllPlayers(head);
            head = sortTeamsByRating(head);
            head = mainMenuxa(head);
            
            head = save(head, "DataText.txt");
            
            free(head);
        } else {
            printf("I need more memmory");
        }
    } else {
        printf("no memmery");
    }
    return 0;
}
