# ../_libs/messages/types/saytext.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Core
from core import GameEngine
#   Messages
from messages.base import BaseMessage
from messages.base import MessageTypes


# =============================================================================
# >> CLASSES
# =============================================================================
class SayText(BaseMessage):
    '''Class used to send SayText messages'''

    def __init__(self, message, index=0, users=(), **tokens):
        '''Initializes the class instance and stores the given values'''

        # Store all the base attributes
        self.message = message
        self.users = users
        self.tokens = tokens

    def _send_message(self, recipients, message):
        '''Sends the message to the given recipients'''

        # Create the UserMessage
        UserMessage = self._get_usermsg_instance(recipients)

        # Write the index to the UserMessage
        UserMessage.WriteByte(self.index)

        # Write 1 to the UserMessage
        UserMessage.WriteByte(1)

        # Write the message to the UserMessage
        UserMessage.WriteString('\x01' + message)

        # Send the message to the recipients
        GameEngine.MessageEnd()

    def _send_protobuf_message(self, recipients, message):
        '''Sends a protobuf message to the given recipients'''

        # Get the usermessage instance
        UserMessage = self._get_protobuf_instance()

        # Set the message's index
        UserMessage.set_ent_idx(self.index)

        # Set the message's text
        # Adding ESCSOH to the start of the message seems to fix colors passed
        #   at the begining.
        UserMessage.set_text('\x1B\x01' + message)

        # Set the chat for the index
        UserMessage.set_chat(False)

        # Send the message
        GameEngine.SendUserMessage(
            recipients, MessageTypes[self.__class__.__name__], UserMessage)
