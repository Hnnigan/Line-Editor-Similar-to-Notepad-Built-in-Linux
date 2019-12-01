/* Harsh Nigam
roll no: 24
line editor
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct node
{
  char str[80];
  struct node *next;
}
node;

void
display (node * start, int n)
{
  node *temp;
  int i = 1;
  if (start == NULL)
    {
      printf ("file is empty");
      return;
    }
  //temp = (node *) malloc (sizeof (node));
  temp = start;
  while (temp->next != NULL)
    {
      if (i == n)
	{
	  printf ("\n%d: %s", i, temp->str);
	  return;
	}
      i++;
      temp = temp->next;
    }
  printf ("\n%d: %s", i, temp->str);
}

void
display1 (node * start, int n1, int n2)
{
  node *temp;
  int i = 1;
  //temp = (node *) malloc (sizeof (node));
  temp = start;
  if (start == NULL)
    {
      printf ("file is empty");
      return;
    }

  while (temp != NULL)
    {
      if (i >= n1 && i <= n2)
	printf ("\n%d: %s", i, temp->str);
      temp = temp->next;
      i++;
    }
}

void
insert (node ** start, char str1[80], int pos)
{
  node *temp, *temp1;
  int i = 1;
  //printf ("Pos: %d", pos);
  temp = (node *) malloc (sizeof (node));
  strcpy (temp->str, str1);
  if (*start == NULL)
    {
      temp->next = NULL;
      *start = temp;
    }
  else if (pos == 0)
    {
      temp1 = *start;
      while (temp1->next != NULL)
	temp1 = temp1->next;
      temp1->next = temp;
      temp->next = NULL;
    }
  else if (pos == 1)
    {
      temp->next = *start;
      *start = temp;
    }
  else
    {
      temp1 = *start;
      while (temp1->next != NULL && i < pos - 1)
	{
	  temp1 = temp1->next;
	  i++;
	}
      temp->next = temp1->next;
      temp1->next = temp;
    }
}

void
delete1 (node ** start, int pos)
{
  int i;
  node *temp, *temp1;
  if (*start == NULL)
    {
      // printf ("file is empty");
      return;
    }
  if ((*start)->next == NULL)
    {
      temp = *start;
      //printf ("\n deleting line: %s", temp->str);
      free (temp);
      *start = NULL;
      return;
    }
  else
    {
      if (pos == 1)
	{
	  temp = *start;
	  *start = (*start)->next;
	  //  printf ("\n deleting line: %s", temp->str);
	  free (temp);
	}
      else
	{
	  temp1 = *start;
	  i = 1;
	  while (temp1->next->next != NULL && i < pos - 1)
	    {
	      temp1 = temp1->next;
	    }
	  temp = temp->next;
	  temp1->next = temp->next;
	  //printf ("\n deleting line %s", temp->str);
	}
    }
}

void
delete2 (node ** start, int n1, int n2)
{
  int i, j;
  node *temp, *temp1;
  if (*start == NULL)
    {
      printf ("\n file is empty");
      return;
    }
  if ((*start)->next == NULL)
    {
      temp = *start;
      printf ("\n deleting line: %s", temp->str);
      free (temp);
      *start = NULL;
      return;
    }
  else if (n1 == n2)
    {
      if (n1 == 1)
	{
	  temp = *start;
	  *start = (*start)->next;
	  printf ("\ndeleting line %s", temp->str);
	  free (temp);
	}
      else
	{
	  temp1 = *start;
	  i = 1;
	  while (temp1->next != NULL && i < n1 - 1)
	    {
	      temp1 = temp1->next;
	      i++;
	    }
	  temp = temp1->next;
	  temp1->next = temp->next;
	  printf ("\n deleting line %s", temp->str);
	}
    }
  else
    {
      temp1 = *start;
      i = n2 - n1 + 1;
      j = 2;
    label:while (temp1->next != NULL && i > 0)
	{
	  if (n1 == 1)
	    {
	      while (*start != NULL && n1 != n2 + 1)
		{
		  temp = *start;
		  *start = (*start)->next;
		  printf ("\n deleting line: %s", temp->str);
		  free (temp);
		  n1++;
		}
	      return;
	    }
	  else
	    {
	      if (j >= n1 && j <= n2)
		{
		  temp = temp1->next;
		  temp1->next = temp->next;
		  printf ("\n deleting line: %s", temp->str);
		  free (temp);
		  i--;
		  j++;
		  goto label;
		}
	    }
	  temp1 = temp1->next;
	  j++;
	}
    }
}

void
copy1 (node ** start, int n1, int n2)
{
  int i = 1;
  node *temp1 = *start, *temp2 = *start, *temp3 = *start;
  i = 1;
  while ((i < n1) && (temp1->next != NULL))
    {
      temp1 = temp1->next;
      i++;
    }
  i = 1;
  while ((i < n2) && (temp2->next != NULL))
    {
      temp2 = temp2->next;
      i++;
    }

  insert (&(*start), temp1->str, i);
}

void
move1 (node ** start, int n1, int n2)
{
  int i = 1;
  char s[80];
  node *temp1 = *start, *temp2 = *start;
  while (i < n1)
    {
      temp1 = temp1->next;
      i++;
    }
  i = 1;
  while (i < n2)
    {
      temp2 = temp2->next;
      i++;
    }
  strcpy (s, temp1->str);
  strcpy (temp1->str, temp2->str);
  strcpy (temp2->str, s);
}

void
move2 (node ** start, int n1, int n2, int n3)
{
  node *temp = NULL, *temp2, *temp3, *temp1;
  int i = 1, j;
  temp1 = *start;
  while (temp1 != NULL)
    {
      if (i < n1 || i > n2)
	insert (&temp, temp1->str, 0);
      temp1 = temp1->next;
      i++;
    }
  i = 1;
  temp1 = *start;

  while (temp1->next != NULL && i < n1)
    {
      temp1 = temp1->next;
      i++;
    }
  i = n2 - n1 + 1;
  j = n3;
  while (temp1 != NULL && i > 0)
    {

      insert (&temp, temp1->str, j);
      temp1 = temp1->next;

      j++;
      i--;
    }
  while (*start != NULL)
    {
      delete1 (&(*start), 1);
    }
  *start = temp;
}

void
copy2 (node ** start, int n1, int n2, int n3)
{
  node *temp = NULL, *temp1, *temp2, *temp3;
  int i = 1;
  temp1 = *start;
  while (temp1 != NULL)
    {
      insert (&temp, temp1->str, 0);
      temp1 = temp1->next;
    }
  temp1 = *start;
  while (i < n1)
    {
      i++;
      temp1 = temp1->next;
    }
  temp2 = temp;
  i = 1;
  while (i < n3 - 1)
    {
      i++;
      temp2 = temp2->next;
    }
  i = 1;
  while (i < n2)
    {
      temp3 = ((node *) malloc (sizeof (node)));
      strcpy (temp3->str, temp1->str);
      temp3->next = temp2->next;
      temp2->next = temp3;
      temp1 = temp1->next;
      temp2 = temp2->next;
      i++;
    }
  while (*start != NULL)
    delete1 (&(*start), 1);
  *start = temp;
}

void
save_f (node * start, char f_name[15])
{
  FILE *fp;
  node *temp;
  temp = start;
  fp = fopen (f_name, "w");
  if (fp == NULL)
    {
      printf ("\nfile opening error");
      exit (1);
    }
  while (temp != NULL)
    {
      fprintf (fp, "%s", temp->str);
      temp = temp->next;
    }
  fclose (fp);
}

void
search (node * start, char string[80], int n1, int n2)
{
 
  int pos = 1;
  node *temp;
  temp = start;
  while (temp != NULL)
    {
      if (strstr (temp->str, string) != NULL && (pos >= n1 && pos <= n2))
	{

	  printf ("\n string found: %s at pos %d", temp->str, pos);
	  return;
	}
      temp = temp->next;
      pos++;
    }
  printf ("\n string not found");
}

void
pattern (node * start, int n1, int n2)
{
  int i;
  node *t;
  char line[20];
  if (n1 < 0 || n2 < 0)
    {
      printf ("\n Invalid");
    }
  else
    {
      printf ("\n Pattern ");
      fflush (stdin);
      gets (line);
      for (i = 1, t = start; i < n1; i++, t = t->next);
      for (; i <= n2; t = t->next)
	{
	  if (strstr (t->str, line))
	    {
	      printf ("\n Line is: %d : %s", i, t->str);
	    }
	  i++;
	}
    }
}

void
main (int argc, char *argv[])
{
  int count_l = 0, tokens, x1, y, n, flag1 = 0, flag2 = 0, flag3 = 0, flag4 =
    0, flag = 0;
  char f_name[15], ch, line[80], str[80], t1[2], t2[2], t3[2], t4[2], t5[2],
    command[10];
  FILE *fp;
  node *start = NULL, *temp;
  if (argc > 2)
    {
      printf ("incorrect no of argument is passed");
      exit (1);
    }
  if (argc == 2)
    {
      strcpy (f_name, argv[1]);
      flag1 = 1;
      flag2 = 1;
      flag4 = 1;

    }

  fp = fopen (f_name, "r");
  if (fp == NULL)
    {
      flag3 = 1;
      goto label1;

    }
  while (fgets (line, 80, fp))
    {
      insert (&start, line, 0);
      count_l++;
    }
  fclose (fp);

label1:printf ("\n number of lines are: %d", count_l);

  while (1)
    {
      printf ("\n?");
      fflush (stdin);
      gets (command);
      tokens = sscanf (command, "%s%s%s%s%s", t1, t2, t3, t4, t5);

      switch (tokens)
	{
	case 1:
	  if (strcmp (t1, "p") == 0)
	    display (start, 1);
	  else if (strcmp (t1, "a") == 0)
	    {
	      printf ("Enter the line:");
	      fflush (stdin);
	      gets (str);
	      flag = 1;
	      flag2 = 1;
	      while (strcmp (str, ".") != 0)
		{
		  strcat (str, "\n");
		  insert (&start, str, 0);
		  printf ("\n Enter next line");
		  fflush (stdin);
		  gets (str);
		}
	    }
	  else if (strcmp (t1, "i") == 0)
	    {
	      printf ("enter the line:");
	      fflush (stdin);
	      gets (str);
	      x1 = 1;
	      flag = 1;
	      flag2 = 1;
	      while (strcmp (str, ".") != 0)
		{
		  strcat (str, "\n");
		  insert (&start, str, x1);
		  printf ("\nenter next line:");
		  fflush (stdin);
		  gets (str);
		  x1++;
		}
	    }
	  else if (strcmp (t1, "s") == 0)
	    {
	      flag2 = 0;
	      if (flag1)
		{
		  save_f (start, f_name);
		  printf ("\nChanges are saved...!!!");

		}
	      else
		{
		  printf ("\nEnter the filename: ");
		  fflush (stdin);
		  scanf ("%s", f_name);
		  getchar ();
		  flag1 = 1;
		  flag4 = 1;
		  fp = fopen (f_name, "r");
		  if (fp == NULL)
		    save_f (start, f_name);
		  else
		    {
		      printf
			("\nfile already exists .. Do you want to save changes(y/n)");
		      scanf ("%c", &ch);
		      if (ch == 'y' || ch == 'Y')
			{
			  save_f (start, f_name);
			  printf ("\nChanges are saved...!!!");
			  getchar ();
			}
		      else
			{
			  flag1 = 0;
			  flag4 = 0;
			  flag2 = 1;
			  printf ("\nChanges are not saved...!!!");
			  getchar ();
			}
		    }
		}
	    }
	  else if (strcmp (t1, "d") == 0)
	    {
	      delete2 (&start, 1, 1);
	      flag2 = 1;
	      flag = 1;
	    }
	  else if (strcmp (t1, "q") == 0)
	    {

	      if (!flag)
		exit (0);
	      if (flag1 && flag2)
		{
		  printf ("\nDo you want to save changes(y/n)");
		  scanf ("%c", &ch);
		  if (ch == 'y' || ch == 'Y')
		    {
		      save_f (start, f_name);
		      printf ("\nChanges are saved...!!!");
		    }
		  else
		    printf ("\nChanges are not saved...!!!");
		}
	      else if (!flag4)
		{
		  printf ("\nDo you want to save changes in file(y/n)");
		  scanf ("%c", &ch);
		  if (ch == 'y' || ch == 'Y')
		    {
		      printf ("\nEnter the filename: ");
		      fflush (stdin);
		      scanf ("%s", f_name);
		      getchar ();
		      flag1 = 1;
		      fp = fopen (f_name, "r");
		      if (fp == NULL)
			save_f (start, f_name);
		      else
			{
			  printf ("\nDo you want to alter the file(y/n)");
			  scanf ("%c", &ch);
			  if (ch == 'y' || ch == 'Y')
			    {
			      save_f (start, f_name);
			      printf ("\nChanges are saved...!!!");
			    }
			  else
			    printf ("\nChanges are not saved...!!!");
			}
		    }
		}
	      exit (0);
	    }


	  /* else if (strcmp (t1, "f") == 0)
	     {
	     printf ("enter the line u want search");
	     fflush (stdin);
	     gets (str);
	     search (start, str);
	     } */
	  else
	    printf ("invalid command");
	  break;
	case 2:
	  if (strcmp ("p", t1) == 0)
	    {
	      if (atoi (t2) <= 0)
		printf ("\n not allowed");
	      else
		display (start, atoi (t2));
	    }
	  else if (strcmp ("i", t1) == 0)
	    {
	      if (atoi (t2) <= 0)
		printf ("\n invalid...");
	      else
		{
		  printf ("\nenter the line");
		  fflush (stdin);
		  gets (str);
		  x1 = atoi (t2);
		  while (strcmp (str, ".") != 0)
		    {
		      strcat (str, "\n");
		      insert (&start, str, x1);
		      printf ("\n Enter the next line:");
		      fflush (stdin);
		      gets (str);
		      x1++;
		    }
		}
	    }
	  else if (strcmp (t1, "d") == 0)
	    {
	      flag = 1;
	      for (temp = start, x1 = 0; temp != NULL;
		   temp = temp->next, x1++);

	      if (atoi (t2) <= 0)
		printf ("\nInvalid command...!!!");
	      else if (atoi (t2) > x1)
		delete2 (&start, x1, x1);
	      else
		delete2 (&start, atoi (t2), atoi (t2));
	    }
	  else
	    printf ("\n invalid command");
	  break;

	case 3:
	  if (strcmp (t1, "p") == 0)
	    {
	      if (atoi (t2) <= 0 || atoi (t3) <= 0 || (atoi (t2) > atoi (t3)))
		printf ("\nInvalid command");
	      else
		display1 (start, atoi (t2), atoi (t3));
	    }
	  else if (strcmp (t1, "d") == 0)
	    {
	      flag = 1;
	      if (atoi (t2) <= 0 || atoi (t3) <= 0 || (atoi (t2) > atoi (t3)))
		printf ("\nInvalid command");
	      else
		delete2 (&start, atoi (t2), atoi (t3));
	    }
	  else if (strcmp (t1, "c") == 0)
	    {
	      flag = 1;
	      if (atoi (t2) < 1 || (atoi (t2) > atoi (t3)))
		printf ("\nInvalid Command...!!!");
	      else
		copy1 (&start, atoi (t2), atoi (t3));
	    }
	  else if (strcmp (t1, "m") == 0)
	    {
	      flag = 1;
	      if (atoi (t2) < 1 || atoi (t3)<1)
		printf ("\nInvalid Command...!!!");
	      else
		move1 (&start, atoi (t2), atoi (t3));
	    }
	  else if (strcmp (t1, "f") == 0)
	    {
	      if (atoi (t2) < 1 || (atoi (t2) > atoi (t3)))
		printf ("\nInvalid Command...!!!");
	      printf ("enter the line you want to search : ");
	      fflush (stdin);
	      gets (str);
	      search (start, str, atoi (t2), atoi (t3));
	    }
	  else
	    printf ("\n invalid command");
	  break;

	case 4:
	  if (strcmp (t1, "c") == 0)
	    {
	      flag = 1;
	      if (atoi (t2) < 1 || (atoi (t2) > atoi (t3)))
		printf ("\nInvalid Command...!!!");
	      else
		copy2 (&start, atoi (t2), atoi (t3), atoi (t4));
	    }
	  else if (strcmp (t1, "m") == 0)
	    {
	      flag = 1;
	      if (atoi (t2) < 1 || (atoi (t2) > atoi (t3)))
		printf ("\nInvalid Command...!!!");
	      else
		move2 (&start, atoi (t2), atoi (t3), atoi (t4));
	    }
	  else
	    printf ("invalid command...!!!");
	  break;
	default:
	  printf ("\n Invalid command...!!!");
	}
    }
}
