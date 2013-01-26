# ../_libs/translations/strings.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Binascii
from binascii import unhexlify
#   Configobj
from configobj import ConfigObj
#   String
from string import Template
#   Re
from re import compile
from re import IGNORECASE
from re import VERBOSE

# Source.Python Imports
from paths import TRANSLATION_PATH
from paths import GAME_PATH
#   Translations
from translations.manager import LanguageManager


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get an re.compile instance to correct all double escaped strings
_double_escaped_pattern = compile(r'''(\\(?:(?P<octal>[0-7]{1,3})|
    x(?P<hexadecimal>[0-9|a-f]{2})|(?P<notation>a|b|e|f|n|r|s|t|v|x)))''',
    IGNORECASE | VERBOSE)


# =============================================================================
# >> CLASSES
# =============================================================================
class LangStrings(dict):
    '''Dictionary class used to store all strings for an addon'''

    def __init__(self, infile, encoding='utf_8'):
        '''Adds all strings as TranslationStrings
            instances and fixes double escaped strings'''

        # Get the path to the given file
        self._mainfile = TRANSLATION_PATH.joinpath(infile + '.ini')

        # Does the file exist?
        if not self._mainfile.isfile():

            # Raise an error
            raise FileNotFoundError('No file found at %s' % self._mainfile)

        # Get the path to the server specific file
        self._serverfile = self._mainfile.parent.joinpath(
            self._mainfile.namebase + '_server.ini')

        # Does the server specific file exist?
        if not self._serverfile.isfile():

            # Create the server specific file
            self._create_server_file()

        # Get the strings from the main file
        main_strings = ConfigObj(self._mainfile, encoding=encoding)

        # Get any strings from the server specific file
        server_strings = ConfigObj(self._serverfile, encoding=encoding)

        # Merge the two ConfigObj instances together
        main_strings.merge(server_strings)

        # Loop through all strings
        for key in main_strings:

            # Create an empty dictionary to store
            # language strings for the current string
            set_strings = {}

            # Loop through all languages for the current string
            for lang in main_strings[key]:

                # Get the shortname of the current language
                language = LanguageManager.get_language(lang)

                # Was the language found?
                if language is None:

                    # Do not add this translation
                    # Possibly raise an error silently here
                    continue

                # Get the language's string and fix any escaped strings
                set_strings[language] = self._replace_escaped_sequences(
                    main_strings[key][lang])

                # Add the new dictionary as a TranslationStrings
                # instance for the current string
                self[key] = TranslationStrings(set_strings)

                # Get the tokens for the TranslationStrings instance
                self[key]._get_tokens()

                # Was a discrepancy found when getting tokens?
                if self[key].tokens is None:

                    # Silently raise an error

                    # Remove the item from the dictionary
                    del self[key]

    def _create_server_file(self):
        '''Creates a server specific langstrings file'''

        # Get the server specific file's ConfigObj instance
        server_file = ConfigObj(self._serverfile)

        # Set the initial comments to explain what the file is for
        server_file.initial_comment = [
            'This file has been created to host new language translations for',
            'the ../%s' % self._mainfile.replace(GAME_PATH, ''),
            'file for this particular server.',
        ]

        # Write the server specific file
        server_file.write()

    @staticmethod
    def _replace_escaped_sequences(given_string):
        '''Fixes all double escaped strings'''

        # Loop through all matches
        for escaped_match in set(_double_escaped_pattern.finditer(given_string)):
            
            # Get the match as a string
            matching_string = escaped_match.group()
            
            # Get a dictionnary of all groups
            matching_groups = escaped_match.groupdict()
            
            # Are we matching any octal sequences?
            if matching_groups['octal']:
                
                # Replace it
                given_string = given_string.replace(matching_string,
                    chr(int(matching_groups['octal'])))
                    
            # Otherwise, are we matching any hexadecimal sequences?
            elif matching_groups['hexadecimal']:
                
                # Replace it
                given_string = given_string.replace(matching_string,
                    str(unhexlify(matching_groups['hexadecimal']),
                    encoding='ascii'))
                    
            # Otherwise, that means we are matching a notation
            else:
                
                # Replace it
                given_string = given_string.replace(matching_string,
                    unicode_escape_decode(matching_string)[0])
                    
        # Return the replaced string
        return given_string


class TranslationStrings(dict):
    '''Class used to store grouped language strings'''

    def _get_tokens(self):
        '''Gets all tokens for the instance's strings'''

        # Store tokens as an empty dictionary
        self.tokens = False

        # Loop through all languages provided for the string
        for language in self:

            # Store an empty dictionary for the current language
            current_tokens = {}

            # Loop through all tokens in the current string
            for matching_token in set(
                Template.pattern.finditer(self[language])):

                # Get the groups for the current string's tokens
                matching_groups = matching_token.groupdict()

                # Are the groups invalid?
                if matching_groups['invalid']:

                    # Move to the next token
                    continue

                # Get the current token string
                matching_string = matching_token.group()

                # Is the current token escaped?
                if matching_groups['escaped']:

                    # Replace the token in the string
                    self[language] = self[language].replace(
                        matching_string, Template.delimiter)

                # Is the current token named or braced?
                else:

                    # Get the current token's name
                    token_name = (matching_token.group('named')
                        or matching_token.group('braced')

                    # Store the token's name with its token string
                    current_tokens[token_name] = matching_string

            # Has the instance's tokens been set?
            if self.tokens != False:

                # Set the instance's tokens to the current tokens
                self.tokens = current_tokens

            # Do the current tokens equal the instance's tokens
            elif self.tokens != current_tokens:

                # Set the instance's tokens to None to remove
                # the instance from the LangStrings dictionary
                self.tokens = None

                # Return from the loop
                return

    def get_string(self, language, **given_tokens):
        '''Returns the language string for the given language/tokens'''

        # Get the language shortname to be used
        language = self.get_language(language)

        # Was a valid language found?
        if language is None:

            # Return an empty string
            return '' # raise an error silently here, in case looping through players

        # Get the language specific message
        message = self[language]

        # Loop through all tokens
        for token in given_tokens:

            # Is the current token in the strings token dictionary?
            if not token in self.tokens:

                # No need to replace this token
                continue

            # Replace the token
            message.replace(self.tokens[token], given_tokens[token])

        # Return the message
        return message

    def get_language(self, language):
        '''Returns the language to be used'''

        # Get the given language's shortname
        language = LanguageManager.get_language(language)

        # Was a language found?
        if not language is None:

            # Return the language
            return language

        # Is the server's default language in the dictionary?
        if LanguageManager.default in self:

            # Return the server's default language
            return LanguageManger.default

        # Is the server's fallback language in the dictionary?
        if LanguageManager.fallback in self:

            # Return the server's fallback language
            return LanguageManager.fallback

        # Return None as the language, as no language has been found
        return None
