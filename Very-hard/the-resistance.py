import sys

morse_alphabet = {
    ".-": "A",
    "-...": "B",
    "-.-.": "C",
    "-..": "D",
    ".": "E",
    "..-.": "F",
    "--.": "G",
    "....": "H",
    "..": "I",
    ".---": "J",
    "-.-": "K",
    ".-..": "L",
    "--": "M",
    "-.": "N",
    "---": "O",
    ".--.": "P",
    "--.-": "Q",
    ".-.": "R",
    "...": "S",
    "-": "T",
    "..-": "U",
    "...-": "V",
    ".--": "W",
    "-..-": "X",
    "-.--": "Y",
    "--..": "Z",
}


def can_word_be_composed_by_dictio(word, dictio):

    for key in dictio:
        word = word.replace(key, "")

    if word == "":
        return True

    for key in dictio:
        if word in key:
            return True

    return False


def get_number_of_messages_that_could_composed_by_dictio(word, dictio):
    nb_possible_messages = 0
    if len(word) == 0:
        return 1

    for k in range(len(word) + 1):
        if word[:k] in dictio:
            nb_possible_messages += (
                get_number_of_messages_that_could_composed_by_dictio(word[k:], dictio)
            )

    return nb_possible_messages


processed_morse_code = {}


def get_possible_words_from_morse_code(morse_code, word_dictio, previous_words):

    to_be_memorized = True

    if not can_word_be_composed_by_dictio(previous_words, word_dictio):
        # print("invalid previous_words ..." , previous_words, file=sys.stderr, flush=True)
        return []

    # Use memoization for more efficient and faster computation
    if morse_code in processed_morse_code:
        return processed_morse_code[morse_code]

    if len(morse_code) <= 0:
        return [""]
    else:
        possible_messages = []

        for i in range(
            1, min(5, len(morse_code) + 1)
        ):  # without the min(), you will get a lot of duplicated solutions !!
            if morse_code[:i] in morse_alphabet:
                if morse_alphabet[morse_code[:i]] in set("".join(word_dictio)):
                    previous_words += morse_alphabet[morse_code[:i]]
                    possible_messages_temp = get_possible_words_from_morse_code(
                        morse_code[(i):], word_dictio, previous_words
                    )
                    if possible_messages_temp == []:
                        print(
                            " to_be_memorized = False: ",
                            processed_morse_code,
                            file=sys.stderr,
                            flush=True,
                        )
                        to_be_memorized = False
                    for j in possible_messages_temp:
                        possible_messages.append(morse_alphabet[morse_code[:(i)]] + j)
                    previous_words = previous_words[:-1]
        # print("possible messages: ", possible_messages , file=sys.stderr, flush=True)

        # Do not save the solution if there are any invalid previous words: to be implemented ...

        if to_be_memorized:
            processed_morse_code[morse_code] = possible_messages

        return possible_messages


word_dictio = []
number_of_possible_messages = 0
possible_messages = []

morse_sequence = input()
n = int(input())
for i in range(n):
    w = input()
    word_dictio.append(w)

possible_messages = get_possible_words_from_morse_code(morse_sequence, word_dictio, "")
print("possible messages: ", possible_messages, file=sys.stderr, flush=True)
for message in possible_messages:
    number_of_possible_messages += get_number_of_messages_that_could_composed_by_dictio(
        message, word_dictio
    )

print(number_of_possible_messages)
