# ../_libs/entities/entity.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Binutils
from Source import Engine
#   Entities
from entities.functions import Functions
from entities.keyvalues import KeyValues
from entities.offsets import Offsets
from entities.properties import Properties
from entities.specials import _EntitySpecials


# =============================================================================
# >> CLASSES
# =============================================================================
class BaseEntity(_EntitySpecials):
    '''Class used to interact directly with entities'''

    index = 0
    edict = 0
    entities = None

    def __new__(cls, index, *entities):
        '''Override the __new__ class method to verify the given index
            is of the correct entity type and add the index attribute'''

        # Get the given indexes edict
        edict = Engine.PEntityOfEntIndex(index)

        # Is the edict valid?
        if edict is None:

            # If not raise an error
            raise ValueError('Index "%s" is not a proper index' % index)

        # Create the object
        self = object.__new__(cls)

        # Set the entity's base attributes
        self.index = index
        self.edict = edict
        self.entities = set(entities)
        self.entities.add('entity')

        # Return the instance
        return self

    def __getattr__(self, attr):
        '''Finds if the attribute is valid and returns the appropriate value'''

        # Loop through all instances (used to get edict/IPlayerInfo attributes)
        for instance in self.instances:

            # Does the current instance contain the given attribute?
            if hasattr(instance, attr):

                # Return the instance's value for the given attribute
                return getattr(instance, attr)

        # Is this an inherited class and does
        # the inheriting class have the property?
        if self.__class__ != BaseEntity and hasattr(self.__class__, attr):

            # Get the attribute
            return getattr(self.__class__, attr).fget(self)

        # Is the attribute a property of this entity?
        if attr in self.properties:

            # Return the property's value
            return self._get_property(attr)

        # Is the attribute a keyvalue of this entity?
        if attr in self.keyvalues:

            # Return the keyvalue's value
            return self._get_keyvalue(attr)

        # Is the attribute an offset of this entity?
        if attr in self.offsets:

            # Return the offset's value
            return self._get_offset(attr)

        # Is the attribute a function of this entity?
        if attr in self.functions:

            # Return the function
            return self._get_function(attr)

        # If the attribute is not found, raise an error
        raise AttributeError('Attribute "%s" not found' % attr)

    def _get_property(self, item):
        '''Gets the value of the given property'''

        # Get the property's type
        prop_type = self.properties[item].type

        # Is the property's type a known type?
        if not hasattr(self.edict, 'GetProp%s' % prop_type):

            # If not a proper type, raise an error
            raise TypeError('Invalid property type "%s"' % prop_type)

        # Get the property's prop
        prop = self.properties[item].prop

        # Get the property's value
        value = getattr(self.edict, 'GetProp%s' % prop_type)(prop)

        # Is the property a True/False property?
        if 'True' in self.properties[item]:

            # Return if the current value equals the "True" value
            return value == self.properties[item]['True']

        # Return the value of the property
        return value

    def _get_keyvalue(self, item):
        '''Gets the value of the given keyvalue'''

        # Return the value of the given keyvalue
        return self.edict.GetKeyValue(item)

    def _get_offset(self, item):
        '''Gets teh value of the given offset'''

        # Get the offset's type
        offset_type = self.offsets[item].type

        # Is the offset's type a known type?
        if not hasattr(Binutils, 'GetLoc%s' % offset_type):

            # If not a proper type, raise an error
            raise TypeError('Invalid offset type "%s"' % offset_type)

        # Return the value of the offset
        return getattr(Binutils, 'GetLoc%s' % offset_type)(
            self.pointer + self.offsets[item].offset)

    def _get_function(self, item):
        '''Calls a dynamic function'''

        # Does the entity's pointer need to be added to the arguments?
        if self.functions[item].pointer_index != -1:

            # Set the entity's pointer as the current one
            self.functions[item].current_pointer = self.pointer

        # Return the pre call function method
        return self.functions[item]._pre_call_function

    def __setattr__(self, attr, value):
        '''Finds if the attribute is value and sets its value'''

        # Does the class have the given attribute?
        if hasattr(self.__class__, attr):

            # Set the attribute
            object.__setattr__(self, attr, value)

            # No need to go further
            return

        # Loop through all instances
        # (used to set using edict/IPlayerInfo attributes)
        for instance in self.instances:

            # Does the current instance contain the given attribute?
            if hasattr(instance, attr):

                # Get the attribute's instance and use it to set the value
                setattr(instance, attr, value)

                # No need to go further
                return

        # Is this an inherited class and does
        # the inheriting class have the property?
        if self.__class__ != BaseEntity and hasattr(self.__class__, attr):

            # Get the attribute
            return getattr(self.__class__, attr).fset(self, value)

        # Is the attribute a property of this entity?
        if attr in self.properties:

            # Set the property's value
            self._set_property(attr, value)

        # Is the attribute a keyvalue of this entity?
        elif attr in self.keyvalues:

            # Set the keyvalue's value
            self._set_keyvalue(attr, value)

        # Is the attribute an offset of this entity?
        elif attr in self.offsets:

            # Set the offset's value
            self._set_offset(attr, value)

        # Was the attribute not found?
        else:

            # If the attribute is not found, raise an error
            raise LookupError('Attribute "%s" not found' % attr)

    def _set_property(self, item, value):
        '''Sets the value of the given propery'''

        # Get the property's type
        prop_type = self.properties[item].type

        # Is the property's type a known type?
        if not hasattr(self.edict, 'SetProp%s' % prop_type):

            # Raise an error
            raise TypeError('Invalid property type "%s"' % prop_type)

        # Get the property's prop
        prop = self.properties[item].prop

        # Is the property a True/False property?
        if 'True' in self.properties[item]:

            # Get the exact value to set the property to
            value = self.properties[item][str(bool(value))]

        # Set the property's value
        getattr(self.edict, 'SetProp%s' % prop_type)(prop, value)

    def _set_keyvalue(self, item, value):
        '''Sets the value of the given keyvalue'''

        # Get the keyvalue's type
        kv_type = self.keyvalues[item]

        # Is the keyvalue's type a known type?
        if not hasattr(self.edict, 'SetKeyValue%s' % kv_type):

            # Raise an error
            raise TypeError('Invalid keyvalue type "%s"' % kv_type)

        # Set the keyvalue's value
        getattr(self.edict, 'SetKeyValue%s' % kv_type)(item, value)

    def _set_offset(self, item, value):
        '''Sets the value of the given offset'''

        # Get the offset's type
        offset_type = self.offsets[item].type

        # Is the offset's type a known type?
        if not hasattr(Binutils, 'SetLoc%s' % offset_type):

            # If not a proper type, raise an error
            raise TypeError('Invalid offset type "%s"' % offset_type)

        # Set the offset's value
        getattr(Binutils, 'SetLoc%s' % offset_type)(
            self.pointer + self.offsets[item].offset, value)

    def get_color(self):
        '''Returns a 4 part tuple (RGBA) for the entity's color'''

        # Get the render value
        value = self.render

        # Return a tuple with the RGBA values
        return (
            value & 0xff, (value & 0xff00) >> 8,
            (value & 0xff0000) >> 16, (value & 0xff000000) >> 24)

    def set_color(self, args):
        '''Sets the entity's color to the given RGBA values'''

        # Are the the correct number of arguments?
        if not len(args) in (3, 4):

            # Raise an error
            raise TypeError(
                'set_color() requires 3 or 4 ' +
                'arguments, %s were given' % len(args))

        # Get the RGB values
        red, green, blue = args[:3]

        # Get the value using the RGB values
        value = red + (green << 8) + (blue << 16)

        # Was an alpha value passed?
        if len(args) == 3:

            # Get the current alpha value
            alpha = (self.render & 0xff000000)

        # Otherwise
        else:

            # Get the 4th value passed
            alpha = args[3]

        # Add the alpha value to the RGB value
        value += alpha << 24

        # Set the rendermode
        self.rendermode = self.rendermode | 1

        # Set the renderfx
        self.renderfx = self.renderfx | 256

        # Set the entity's color
        self.render = value

    # Set the "color" property for BaseEntity
    color = property(get_color, set_color)

    @property
    def instances(self):
        '''Yields the entity's edict instance'''

        # Yield the edict instance
        yield self.edict

    @property
    def handle(self):
        '''Returns the entity's handle instance'''
        return self.edict.GetNetworkable().GetEntityHandle().GetRefEHandle()

    @property
    def classname(self):
        '''Returns the classname of the entity'''
        return self.edict.GetClassName()

    @property
    def properties(self):
        '''Returns all properties for all entities'''
        return Properties.get_entity_properties(self.entities)

    @property
    def keyvalues(self):
        '''Returns all keyvalues for all entities'''
        return KeyValues.get_entity_keyvalues(self.entities)

    @property
    def offsets(self):
        '''Returns all offsets for all entities'''
        return Offsets.get_entity_offsets(self.entities)

    @property
    def functions(self):
        '''Returns all dynamic calling functions for all entities'''
        return Functions.get_entity_functions(self.entities)

    @property
    def pointer(self):
        '''Returns the entity's pointer'''
        return self.edict.GetUnknown().GetBaseEntity()
