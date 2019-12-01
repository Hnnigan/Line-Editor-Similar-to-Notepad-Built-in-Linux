
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node
{
  char line[80];
  struct Node *next;
};

struct Node *head;
int lines = 0;
int save_flag = 0;
int temp_flag = 0, temp_flag2;
void
append (char line[])
{
  save_flag = 1;
  struct Node *nn;
  nn = malloc (sizeof (struct Node));
  strcpy (nn->line, line);
  nn->next = NULL;

  if (head == NULL)
    {
      head = nn;
    }
  else
    {
      struct Node *temp;
      for (temp = head; temp->next != NULL; temp = temp->next);
      temp->next = nn;
    }
}

void
insert (char line[], int pos)
{
  save_flag = 1;
  struct Node *nn;
  nn = malloc (sizeof (struct Node));
  strcpy (nn->line, line);
  nn->next = NULL;

  if (pos == 1)
    {
      nn->next = head;
      head = nn;
    }
  else
    {
      struct Node *temp;
      int i;
      for (temp = head, i = 1; i < (pos - 1); temp = temp->next, i++);
      nn->next = temp->next;
      temp->next = nn;
    }
}

void
print (int start, int end)
{
  save_flag = 1;
  struct Node *temp;
  int i;
  for (temp = head, i = 1; i < start; i++, temp = temp->next);
  for (i = start; (temp != NULL) && (i <= end); temp = temp->next, i++)
    {
      printf ("%s", temp->line);
    }
}

void
delete (int pos)
{
  save_flag = 1;
  struct Node *dnode;
  struct Node *temp;
  int i;
  if (head == NULL)
    {
      printf ("\n File is empty!");
    }
  else
    {
      if (pos == 1)
	{
	  struct Node *dnode;
	  dnode = head;
	  head->next = head;
	  free (dnode);
	}
      else
	{
	  for (temp = head, i = 1; i < (pos - 1); temp = temp->next, i++);
	  dnode = temp->next;
	  temp->next = dnode->next;
	  free (dnode);
	}
    }
}

void
move (int start, int target)
{
  save_flag = 1;
  struct Node *temp;
  int i;
  char line[80];
  for (temp = head, i = 1; i < start; temp = temp->next, i++);
  strcpy (line, temp->line);
  delete (i);
  insert (line, target);
}

void
copy (int start, int target)
{
  save_flag = 1;
  struct Node *temp;
  int i;
  char line[80];
  for (temp = head, i = 1; i < start; temp = temp->next, i++);
  strcpy (line, temp->line);
  insert (line, target);
}


void
save (char filename[])
{
  save_flag = 0;
  FILE *fp;
  struct Node *temp;
  fflush (stdin);

  fp = fopen (filename, "w");
  for (temp = head; temp != NULL; temp = temp->next)
    {
      fputs (temp->line, fp);
    }

  fclose (fp);
}

void
create_list (char filename[])
{
  FILE *fp;
  fp = fopen (filename, "r");
  char line[80];
  if (fp != NULL)
    {
      while (fgets (line, 80, fp) != NULL)
	{
	  append (line);
	  lines++;
	}
    }

  fclose (fp);
}

void
search (char pattern[80])
{
  int i, j, k, line_len, pattern_len, line_nos = 0;
  struct Node *temp;
  for (temp = head; temp != NULL; temp = temp->next)
    {
      line_nos++;
      pattern_len = strlen (pattern);
      line_len = strlen (temp->line);
      for (k = 0; k < line_len; k++)
	{
	  if (temp->line[k] == pattern[0])
	    {
	      for (j = 0; j < pattern_len; j++, k++)
		{
		  if (temp->line[k] != pattern[j])
		    {
		      break;
		    }
		}
	      if (j == pattern_len)
		{
		  printf
		    ("\n Pattern : %d, found at line no. %d at position %d\n",
		     pattern, line_nos, ((k - pattern_len) + 1));
		}
	      k--;
	    }
	}
    }
}

int
main (int count, char *value[])
{
  FILE *fp;
  char command[20], filename[20], op[5], p1[5], p2[5], p3[5], line[80];
  int cnt, n1, n2, n3, line_no, save_condition, error_flag = 0;

  if (count == 1)
    {
      strcpy (filename, "");
    }
  else if (count == 2)
    {
      if (strcmp (value[1], "line_editor.c") == 0)
	{
	  printf
	    ("\nYou cannot enter the source file for editing.\nPlease enter another name\n");
	  scanf ("%s", filename);
	}

      strcpy (filename, value[1]);
      fp = fopen (filename, "r");
      if (fp != NULL)
	{
	  create_list (filename);
	}
      else
	{
	  save (filename);
	}

    }
  else
    {
      printf ("Invalid arguements!");
    }


  while (1)
    {
    label:printf ("\n? ");
      fflush (stdin);
      gets (command);
      cnt = sscanf (command, "%s%s%s%s", op, p1, p2, p3);

      if (cnt == 1)
	{
	  n1 = 1;
	  n2 = n1;
	  n3 = n2;
	}
      else if (cnt == 2)
	{
	  n1 = atoi (p1);
	  n2 = n1;
	  n3 = n2;
	}
      else if (cnt == 3)
	{
	  n1 = atoi (p1);
	  n2 = atoi (p2);
	  n3 = n2;
	}
      else
	{
	  n1 = atoi (p1);
	  n2 = atoi (p2);
	  n3 = atoi (p3);
	}

      if ((n1 > lines) && (strcmp (op, "i") == 0))
	{
	  n1 = lines + 1;
	}

      if ((cnt > 2) && (strcmp (op, "i") == 0))
	{
	  error_flag = 1;
	}

      if ((n1 > lines) && (strcmp (op, "p") == 0))
	{
	  printf ("\nOut of range!\nOnly %d lines will be printed.", lines);
	  n1 = lines;
	}

      if ((n1 > n2) && (strcmp (op, "p") == 0 || strcmp (op, "d") == 0))
	{
	  int temp = n2;
	  n2 = n1;
	  n1 = temp;
	}

      if ((n2 > lines) && (strcmp (op, "p") == 0))
	{
	  printf ("\nOut of range!\nOnly %d lines will be printed.", lines);
	  n2 = lines;
	}




      if (error_flag != 1)
	{
	  if (strcmp (op, "i") == 0)
	    {
	      line_no = 1;
	      while (1)
		{
		  fflush (stdin);
		  printf ("\n%d", line_no);
		  gets (line);
		  if (strcmp (line, ".") == 0)
		    {
		      break;
		    }
		  strcat (line, "\n");
		  insert (line, n1);
		  n1++;
		  line_no++;
		  lines++;
		}
	    }
	  else if (strcmp (op, "d") == 0)
	    {
	      delete (n1);
	      lines--;
	    }
	  else if (strcmp (op, "a") == 0)
	    {
	      line_no = 1;
	      while (1)
		{
		  fflush (stdin);
		  printf ("\n%d", line_no);
		  gets (line);
		  if (strcmp (line, ".") == 0)
		    {
		      break;
		    }
		  strcat (line, "\n");
		  append (line);
		  line_no++;
		  lines++;
		}
	    }
	  else if (strcmp (op, "c") == 0)
	    {
	      int iterator;
	      for (iterator = n1; iterator <= n2; iterator++)
		{
		  copy (iterator, n3);
		  n3++;
		  lines++;
		}
	    }
	  else if (strcmp (op, "m") == 0)
	    {
	      int iterator;
	      for (iterator = n1; iterator <= n2; n2--)
		{
		  move (iterator, n3);
		}
	    }

	  else if (strcmp (op, "s") == 0)
	    {
	      if (strcmp (filename, "") == 0)
		{
		  printf ("\nEnter filename : \n");
		  scanf ("%s", filename);
		  FILE *fp2 = fopen (filename, "r");
		  if (fp != NULL)
		    {
		      temp_flag = 1;
		    }
		  fclose (fp2);
		}
	      if (temp_flag == 1)
		{
		  printf ("\nDo you want to overwrite the file?\n(1/0)");
		  scanf ("%d", &temp_flag2);
		  if (temp_flag2 == 1)
		    {
		      printf ("\nFile has been overwritten!\n");
		      save (filename);
		    }
		  else
		    {
		      printf ("\nFile was not saved.\n");
		    }
		}
	      else
		{
		  save (filename);
		}
	    }
	  else if (strcmp (op, "f") == 0)
	    {

	      char pattern[80];
	      printf ("\nEnter the pattern to search : \n");
	      fflush (stdin);
	      gets (pattern);
	      search (pattern);
	    }
	  else if (strcmp (op, "p") == 0)
	    {
	      if (cnt == 1)
		{
		  print (1, lines);
		}
	      else
		{
		  print (n1, n2);
		}
	    }
	  else if (strcmp (op, "q") == 0)
	    {
	      if (save_flag == 0)
		{
		  exit (0);
		}
	      else
		{
		  printf ("Do you want to save the file? (1-yes/0-no)\n");
		  scanf ("%d", &save_condition);

		  if (save_condition == 1)
		    {
		      save (filename);
		      exit (0);
		    }
		  else
		    {
		      exit (0);
		    }
		}
	    }
	  else
	    {
	      printf ("Invalid Operation! Re-enter...\n");
	    }
	}
      else
	{
	  printf ("Invalid");
	}
    }

  return 0;
}
