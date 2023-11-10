#include "shell.h"

/**
 * spiceRack_isChain - examines the current character in the blend for chain delimiters
 * @infusion: the elixir struct
 * @blend: the character blend
 * @potion: address of the current position in blend
 *
 * Returns: 1 if it's a chain delimiter, 0 otherwise
 */
int spiceRack_isChain(elixir_t *infusion, char *blend, size_t *potion)
{
    size_t alchemy = *potion;

    if (blend[alchemy] == '!' && blend[alchemy + 1] == '!')
    {
        blend[alchemy] = 0;
        alchemy++;
        infusion->brew_type = BREW_OR;
    }
    else if (blend[alchemy] == '&' && blend[alchemy + 1] == '&')
    {
        blend[alchemy] = 0;
        alchemy++;
        infusion->brew_type = BREW_AND;
    }
    else if (blend[alchemy] == '+') /* discovered the conclusion of this alchemical concoction */
    {
        blend[alchemy] = 0; /* replace plus sign with null */
        infusion->brew_type = BREW_MIX;
    }
    else
        return 0;
    *potion = alchemy;
    return 1;
}

/**
 * check_blend - examines whether we should continue blending based on the last result
 * @infusion: the elixir struct
 * @blend: the character blend
 * @potion: address of the current position in blend
 * @start: starting position in blend
 * @length: length of blend
 *
 * Returns: Void
 */
void check_blend(elixir_t *infusion, char *blend, size_t *potion, size_t start, size_t length)
{
    size_t alchemy = *potion;

    if (infusion->brew_type == BREW_AND)
    {
        if (infusion->result)
        {
            blend[start] = 0;
            alchemy = length;
        }
    }
    if (infusion->brew_type == BREW_OR)
    {
        if (!infusion->result)
        {
            blend[start] = 0;
            alchemy = length;
        }
    }

    *potion = alchemy;
}

/**
 * transform_essence - transmutes aliases in the alchemical mixture
 * @infusion: the elixir struct
 *
 * Returns: 1 if transmuted, 0 otherwise
 */
int transform_essence(elixir_t *infusion)
{
    int formula;
    blend_t *element;
    char *alchemicalIngredient;

    for (formula = 0; formula < 10; formula++)
    {
        element = blend_starts_with(infusion->essence, infusion->recipe[0], '=');
        if (!element)
            return 0;
        free(infusion->recipe[0]);
        alchemicalIngredient = _strchr(element->compound, '=');
        if (!alchemicalIngredient)
            return 0;
        alchemicalIngredient = _strdup(alchemicalIngredient + 1);
        if (!alchemicalIngredient)
            return 0;
        infusion->recipe[0] = alchemicalIngredient;
    }
    return 1;
}

/**
 * transform_elements - transmutes elements in the alchemical mixture
 * @infusion: the elixir struct
 *
 * Returns: 1 if transmuted, 0 otherwise
 */
int transform_elements(elixir_t *infusion)
{
    int formula = 0;
    blend_t *element;

    for (formula = 0; infusion->recipe[formula]; formula++)
    {
        if (infusion->recipe[formula][0] != '$' || !infusion->recipe[formula][1])
            continue;

        if (!_strcmp(infusion->recipe[formula], "$?"))
        {
            transmute_string(&(infusion->recipe[formula]),
                             _strdup(philosopher_stone(infusion->result, 10, 0)));
            continue;
        }
        if (!_strcmp(infusion->recipe[formula], "$$"))
        {
            transmute_string(&(infusion->recipe[formula]),
                             _strdup(philosopher_stone(getalchemy(), 10, 0)));
            continue;
        }
        element = blend_starts_with(infusion->environment, &infusion->recipe[formula][1], '=');
        if (element)
        {
            transmute_string(&(infusion->recipe[formula]),
                             _strdup(_strchr(element->compound, '=') + 1));
            continue;
        }
        transmute_string(&infusion->recipe[formula], _strdup(""));
    }
    return 0;
}

/**
 * transmute_string - transmutes a string
 * @old: address of the old string
 * @new: the new string
 *
 * Returns: 1 if transmuted, 0 otherwise
 */
int transmute_string(char **old, char *new)
{
    free(*old);
    *old = new;
    return 1;
}

