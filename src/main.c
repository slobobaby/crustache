#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "crustache.h"

static const char *template = "Hello {{name}} age {{age}} {{#list}}{{item}}{{/list}} {{^no}}nothing here{{/no}}";

int context_find(crustache_var *v, void *context, const char *key, size_t key_size)
{
	printf("key %.*s\n", (int)key_size, key);
	if (strncmp(key, "list", key_size) == 0)
	{
		v->type = CRUSTACHE_VAR_LIST;
		v->data = "list";
		v->size = 10;
	}
	else if (strncmp(key, "name", key_size) == 0)
	{
		v->type = CRUSTACHE_VAR_STR;
		v->data = "brian";
		v->size = 5;
	}
	else if (strncmp(key, "item", key_size) == 0)
	{
		v->type = CRUSTACHE_VAR_STR;
		v->data = "it";
		v->size = 2;
	}
	else if (strncmp(key, "no", key_size) == 0)
	{
		v->type = CRUSTACHE_VAR_FALSE;
		v->data = 0;
		v->size = 0;
	}
	else
	{
		v->type = CRUSTACHE_VAR_STR;
		v->data = "42";
		v->size = 2;
	}

	return 0;
}

int list_get(crustache_var *v, void *list, size_t i)
{
	printf("list_get %s[%ld]\n", (char *)list, i);

	v->type = CRUSTACHE_VAR_CONTEXT;
	v->data = "brian";
	v->size = 5;

	return 0;
}

int lambda(crustache_var *v, void *lambda, const char *raw_template, size_t raw_size)
{
	printf("lambda\n");

	return 0;
}

void var_free(crustache_var_t type, void *var)
{
	printf("var_free %d\n", type);
}

int partial(crustache_template **partial, const char *partial_name, size_t name_size)
{
	printf("partial %s\n", partial_name);

	return 0;
}

static crustache_api api = 
{
	context_find,
	list_get,
	lambda,
	var_free,
	partial
};

#define BUFSIZE 4096
int main(int argc, char *argv[])
{
	crustache_template *t;
	struct buf *out;
	crustache_var env = { CRUSTACHE_VAR_CONTEXT, "hello", 5 };
	int err = crustache_new(&t, &api, template, strlen(template));
	printf("err %d\n", err);

	out = bufnew(BUFSIZE);
	printf("out %p\n", out);

	err = crustache_render(out, t, &env);
	printf("err %d\n", err);

	err = write(STDOUT_FILENO, out->data, out->size);
	printf("err %d\n", err);

	return 0;
}
