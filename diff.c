#include "parse-options.h"
#include "promisor-remote.h"
	/*
	 * Please update $__git_diff_submodule_formats in
	 * git-completion.bash when you add new formats.
	 */
	/*
	 * Please update $__git_diff_algorithms in git-completion.bash
	 * when you add new algorithms.
	 */
static unsigned parse_color_moved_ws(const char *arg)
		if (!strcmp(sb.buf, "no"))
			ret = 0;
		else if (!strcmp(sb.buf, "ignore-space-change"))
		else {
			ret |= COLOR_MOVED_WS_ERROR;
			error(_("unknown color-moved-ws mode '%s', possible values are 'ignore-space-change', 'ignore-space-at-eol', 'ignore-all-space', 'allow-indentation-change'"), sb.buf);
		}
	    (ret & XDF_WHITESPACE_FLAGS)) {
		error(_("color-moved-ws: allow-indentation-change cannot be combined with other whitespace modes"));
		ret |= COLOR_MOVED_WS_ERROR;
	}
		unsigned cm = parse_color_moved_ws(value);
		if (cm & COLOR_MOVED_WS_ERROR)
	external_diff_cmd = xstrdup_or_null(getenv("GIT_EXTERNAL_DIFF"));
static int fill_mmfile(struct repository *r, mmfile_t *mf,
		       struct diff_filespec *one)
	else if (diff_populate_filespec(r, one, 0))
static unsigned long diff_filespec_size(struct repository *r,
					struct diff_filespec *one)
	diff_populate_filespec(r, one, CHECK_SIZE_ONLY);
			const char *set_sign, const char *set, unsigned reverse, const char *reset,
	int needs_reset = 0; /* at the end of the line */
	fputs(diff_line_prefix(o), file);
	has_trailing_newline = (len > 0 && line[len-1] == '\n');
	if (has_trailing_newline)
		len--;

	has_trailing_carriage_return = (len > 0 && line[len-1] == '\r');
	if (has_trailing_carriage_return)
		len--;

	if (!len && !first)
		goto end_of_line;

	if (reverse && want_color(o->use_color)) {
		fputs(GIT_COLOR_REVERSE, file);
		needs_reset = 1;
	}

	if (set_sign) {
		fputs(set_sign, file);
		needs_reset = 1;
	if (first)
		fputc(first, file);

	if (!len)
		goto end_of_line;

	if (set) {
		if (set_sign && set != set_sign)
			fputs(reset, file);
		needs_reset = 1;
	fwrite(line, len, 1, file);
	needs_reset = 1; /* 'line' may contain color codes. */

end_of_line:
	if (needs_reset)
		fputs(reset, file);
	emit_line_0(o, set, NULL, 0, reset, 0, line, len);
	int indent_off;   /* Offset to first non-whitespace character */
	int indent_width; /* The visual width of the indentation */
struct moved_block {
	struct moved_entry *match;
	int wsd; /* The whitespace delta of this block */
static void moved_block_clear(struct moved_block *b)
{
	memset(b, 0, sizeof(*b));
}

#define INDENT_BLANKLINE INT_MIN

static void fill_es_indent_data(struct emitted_diff_symbol *es)
	unsigned int off = 0, i;
	int width = 0, tab_width = es->flags & WS_TAB_WIDTH_MASK;
	const char *s = es->line;
	const int len = es->len;

	/* skip any \v \f \r at start of indentation */
	while (s[off] == '\f' || s[off] == '\v' ||
	       (s[off] == '\r' && off < len - 1))
		off++;

	/* calculate the visual width of indentation */
	while(1) {
		if (s[off] == ' ') {
			width++;
			off++;
		} else if (s[off] == '\t') {
			width += tab_width - (width % tab_width);
			while (s[++off] == '\t')
				width += tab_width;
		} else {
			break;
		}
	}

	/* check if this line is blank */
	for (i = off; i < len; i++)
		if (!isspace(s[i]))
		    break;

	if (i == len) {
		es->indent_width = INDENT_BLANKLINE;
		es->indent_off = len;
	} else {
		es->indent_off = off;
		es->indent_width = width;
	}
}

static int compute_ws_delta(const struct emitted_diff_symbol *a,
			    const struct emitted_diff_symbol *b,
			    int *out)
{
	int a_len = a->len,
	    b_len = b->len,
	    a_off = a->indent_off,
	    a_width = a->indent_width,
	    b_off = b->indent_off,
	    b_width = b->indent_width;
	int delta;

	if (a_width == INDENT_BLANKLINE && b_width == INDENT_BLANKLINE) {
		*out = INDENT_BLANKLINE;
		return 1;
	}

	if (a->s == DIFF_SYMBOL_PLUS)
		delta = a_width - b_width;
	else
		delta = b_width - a_width;

	if (a_len - a_off != b_len - b_off ||
	    memcmp(a->line + a_off, b->line + b_off, a_len - a_off))
		return 0;
	*out = delta;
	return 1;
				 struct moved_block *pmb,
	int al = cur->es->len, bl = match->es->len, cl = l->len;
	int a_off = cur->es->indent_off,
	    a_width = cur->es->indent_width,
	    c_off = l->indent_off,
	    c_width = l->indent_width;
	int delta;
	 * We need to check if 'cur' is equal to 'match'.  As those
	 * are from the same (+/-) side, we do not need to adjust for
	 * indent changes. However these were found using fuzzy
	 * matching so we do have to check if they are equal. Here we
	 * just check the lengths. We delay calling memcmp() to check
	 * the contents until later as if the length comparison for a
	 * and c fails we can avoid the call all together.
	if (al != bl)
	/* If 'l' and 'cur' are both blank then they match. */
	if (a_width == INDENT_BLANKLINE && c_width == INDENT_BLANKLINE)
		return 0;
	 * The indent changes of the block are known and stored in pmb->wsd;
	 * however we need to check if the indent changes of the current line
	 * match those of the current block and that the text of 'l' and 'cur'
	 * after the indentation match.
	if (cur->es->s == DIFF_SYMBOL_PLUS)
		delta = a_width - c_width;
	else
		delta = c_width - a_width;
	/*
	 * If the previous lines of this block were all blank then set its
	 * whitespace delta.
	 */
	if (pmb->wsd == INDENT_BLANKLINE)
		pmb->wsd = delta;
	return !(delta == pmb->wsd && al - a_off == cl - c_off &&
		 !memcmp(a, b, al) && !
		 memcmp(a + a_off, c + c_off, al - a_off));
			   const struct hashmap_entry *eptr,
			   const struct hashmap_entry *entry_or_key,
	const struct moved_entry *a, *b;
	a = container_of(eptr, const struct moved_entry, ent);
	b = container_of(entry_or_key, const struct moved_entry, ent);

	unsigned int hash = xdiff_hash_string(l->line, l->len, flags);
	hashmap_entry_init(&ret->ent, hash);
		if (o->color_moved_ws_handling &
		    COLOR_MOVED_WS_ALLOW_INDENTATION_CHANGE)
			fill_es_indent_data(&o->emitted_symbols->buf[n]);
		hashmap_add(hm, &key->ent);
				struct moved_block *pmb,
		struct moved_entry *prev = pmb[i].match;
		if (cur && !hm->cmpfn(o, &cur->ent, &match->ent, NULL)) {
			pmb[i].match = cur;
			pmb[i].match = NULL;
					    struct moved_block *pmb,
	hashmap_for_each_entry_from(hm, match, ent) {
			struct moved_entry *prev = pmb[i].match;
			if (!cmp_in_block_with_wsd(o, cur, match, &pmb[i], n))
			/* Advance to the next line */
			pmb[i].match = pmb[i].match->next_line;
		} else {
			moved_block_clear(&pmb[i]);
		}

	free(got_match);
static int shrink_potential_moved_blocks(struct moved_block *pmb,
		while (lp < pmb_nr && pmb[lp].match)
		while (rp > -1 && !pmb[rp].match)
			memset(&pmb[rp], 0, sizeof(pmb[rp]));
 * Returns 0 if the last block is empty or is unset by this function, non zero
 * otherwise.
 *
static int adjust_last_block(struct diff_options *o, int n, int block_length)
		return block_length;
				return 1;
	return 0;
	struct moved_block *pmb = NULL; /* potentially moved blocks */
	int n, flipped_block = 0, block_length = 0;
		enum diff_symbol last_symbol = 0;
			match = hashmap_get_entry(hm, key, ent, NULL);
			match = hashmap_get_entry(hm, key, ent, NULL);
			flipped_block = 0;
			int i;

			for(i = 0; i < pmb_nr; i++)
				moved_block_clear(&pmb[i]);
			flipped_block = 0;
			last_symbol = l->s;
		if (o->color_moved == COLOR_MOVED_PLAIN) {
			last_symbol = l->s;
			l->flags |= DIFF_SYMBOL_MOVED_LINE;
		}
			hashmap_for_each_entry_from(hm, match, ent) {
					if (compute_ws_delta(l, match->es,
							     &pmb[pmb_nr].wsd))
						pmb[pmb_nr++].match = match;
					pmb[pmb_nr].wsd = 0;
					pmb[pmb_nr++].match = match;
			if (adjust_last_block(o, n, block_length) &&
			    pmb_nr && last_symbol != l->s)
				flipped_block = (flipped_block + 1) % 2;
			else
				flipped_block = 0;
		if (pmb_nr) {
			block_length++;
			l->flags |= DIFF_SYMBOL_MOVED_LINE;
			if (flipped_block && o->color_moved != COLOR_MOVED_BLOCKS)
				l->flags |= DIFF_SYMBOL_MOVED_LINE_ALT;
		}
		last_symbol = l->s;
	for(n = 0; n < pmb_nr; n++)
		moved_block_clear(&pmb[n]);
				const char *set_sign, const char *set,
				const char *reset,
				int sign_index, const char *line, int len,
	int sign = o->output_indicators[sign_index];
		emit_line_0(o, set, NULL, 0, reset, sign, line, len);
		emit_line_0(o, set_sign, set, !!set_sign, reset, sign, line, len);
		emit_line_0(o, ws, NULL, 0, reset, sign, line, len);
		emit_line_0(o, set_sign ? set_sign : set, NULL, !!set_sign, reset,
		emit_line_0(o, context, NULL, 0, reset, '\\',
		emit_line_ws_markup(o, set_sign, set, reset,
				    OUTPUT_INDICATOR_CONTEXT, line, len,
		emit_line_ws_markup(o, set_sign, set, reset,
				    OUTPUT_INDICATOR_NEW, line, len,
		emit_line_ws_markup(o, set_sign, set, reset,
				    OUTPUT_INDICATOR_OLD, line, len,
	struct emitted_diff_symbol e = {line, len, flags, 0, 0, s};
static void emit_add_line(struct emit_callback *ecbdata,
static void emit_del_line(struct emit_callback *ecbdata,
static void emit_context_line(struct emit_callback *ecbdata,
	if (ecbdata->opt->flags.suppress_hunk_header_line_count)
		strbuf_add(&msgbuf, atat, sizeof(atat));
	else
		strbuf_add(&msgbuf, line, ep - line);
static struct diff_tempfile *claim_diff_tempfile(void)
{
			emit_del_line(ecb, data, len);
			emit_add_line(ecb, data, len);
	size_one = fill_textconv(o->repo, textconv_one, one, &data_one);
	size_two = fill_textconv(o->repo, textconv_two, two, &data_two);
	ecbdata.ws_rule = whitespace_rule(o->repo->index, name_b);
static void fn_out_diff_words_aux(void *priv,
				  long minus_first, long minus_len,
				  long plus_first, long plus_len,
				  const char *func, long funclen)
	if (xdi_diff_outf(&minus, &plus, fn_out_diff_words_aux, NULL,
			  diff_words, &xpp, &xecfg))
static void diff_filespec_load_driver(struct diff_filespec *one,
				      struct index_state *istate)
		one->driver = userdiff_find_by_path(istate, one->path);
static const char *userdiff_word_regex(struct diff_filespec *one,
				       struct index_state *istate)
	diff_filespec_load_driver(one, istate);
		o->word_regex = userdiff_word_regex(one, o->repo->index);
		o->word_regex = userdiff_word_regex(two, o->repo->index);
static unsigned long sane_truncate_line(char *line, unsigned long len)
		len = sane_truncate_line(line, len);
		emit_add_line(ecbdata, line + 1, len - 1);
		emit_del_line(ecbdata, line + 1, len - 1);
		emit_context_line(ecbdata, line + 1, len - 1);
		if (p->one->oid_valid && p->two->oid_valid &&
		    oideq(&p->one->oid, &p->two->oid)) {
			diff_populate_filespec(options->repo, p->one, 0);
			diff_populate_filespec(options->repo, p->two, 0);
			diffcore_count_changes(options->repo,
					       p->one, p->two, NULL, NULL,
			diff_populate_filespec(options->repo, p->one, CHECK_SIZE_ONLY);
			diff_populate_filespec(options->repo, p->two, CHECK_SIZE_ONLY);
		 * be identical, but since the oid changed, we
void free_diffstat_info(struct diffstat_t *diffstat)
static void checkdiff_consume_hunk(void *priv,
				   long ob, long on, long nb, long nn,
				   const char *func, long funclen)

{
	struct checkdiff_t *data = priv;
	data->lineno = nb - 1;
}

		char *s = xstrfmt("%"PRIuMAX , (uintmax_t)orig_size);
int diff_filespec_is_binary(struct repository *r,
			    struct diff_filespec *one)
		diff_filespec_load_driver(one, r->index);
				diff_populate_filespec(r, one, CHECK_BINARY);
static const struct userdiff_funcname *
diff_funcname_pattern(struct diff_options *o, struct diff_filespec *one)
	diff_filespec_load_driver(one, o->repo->index);
struct userdiff_driver *get_textconv(struct repository *r,
				     struct diff_filespec *one)
	diff_filespec_load_driver(one, r->index);
	return userdiff_get_textconv(r, one->driver);
		textconv_one = get_textconv(o->repo, one);
		textconv_two = get_textconv(o->repo, two);
		    (textconv_one || !diff_filespec_is_binary(o->repo, one)) &&
		    (textconv_two || !diff_filespec_is_binary(o->repo, two))) {
					  textconv_one, textconv_two, o);
		   ( (!textconv_one && diff_filespec_is_binary(o->repo, one)) ||
		     (!textconv_two && diff_filespec_is_binary(o->repo, two)) )) {
			if (oideq(&one->oid, &two->oid)) {
		if (fill_mmfile(o->repo, &mf1, one) < 0 ||
		    fill_mmfile(o->repo, &mf2, two) < 0)
		const char *diffopts;
		mf1.size = fill_textconv(o->repo, textconv_one, one, &mf1.ptr);
		mf2.size = fill_textconv(o->repo, textconv_two, two, &mf2.ptr);
		pe = diff_funcname_pattern(o, one);
			pe = diff_funcname_pattern(o, two);
		ecbdata.ws_rule = whitespace_rule(o->repo->index, name_b);

		diffopts = getenv("GIT_DIFF_OPTS");

		if (xdi_diff_outf(&mf1, &mf2, NULL, fn_out_consume,
				  &ecbdata, &xpp, &xecfg))
	same_contents = oideq(&one->oid, &two->oid);
	if (diff_filespec_is_binary(o->repo, one) ||
	    diff_filespec_is_binary(o->repo, two)) {
			data->added = diff_filespec_size(o->repo, two);
			data->deleted = diff_filespec_size(o->repo, one);
		diff_populate_filespec(o->repo, one, 0);
		diff_populate_filespec(o->repo, two, 0);
		if (fill_mmfile(o->repo, &mf1, one) < 0 ||
		    fill_mmfile(o->repo, &mf2, two) < 0)
		if (xdi_diff_outf(&mf1, &mf2, discard_hunk_line,
				  diffstat_consume, diffstat, &xpp, &xecfg))
	data.ws_rule = whitespace_rule(o->repo->index, attr_path);
	data.conflict_marker_size = ll_merge_marker_size(o->repo->index, attr_path);
	if (fill_mmfile(o->repo, &mf1, one) < 0 ||
	    fill_mmfile(o->repo, &mf2, two) < 0)
	if (diff_filespec_is_binary(o->repo, two))
		if (xdi_diff_outf(&mf1, &mf2, checkdiff_consume_hunk,
				  checkdiff_consume, &data,
static int reuse_worktree_file(struct index_state *istate,
			       const char *name,
			       const struct object_id *oid,
			       int want_file)
	if (!istate->cache)
	if (!want_file && would_convert_to_git(istate, name))
	pos = index_name_pos(istate, name, len);
	ce = istate->cache[pos];
	if (!oideq(oid, &ce->oid) || !S_ISREG(ce->ce_mode))
	    (!lstat(name, &st) && !ie_match_stat(istate, ce, &st, 0)))
int diff_populate_filespec(struct repository *r,
			   struct diff_filespec *s,
			   unsigned int flags)
	    reuse_worktree_file(r->index, s->path, &s->oid, 0)) {
		if (size_only && !would_convert_to_git(r->index, s->path))
		if (convert_to_git(r->index, s->path, s->data, s->size, &buf, conv_flags)) {
			type = oid_object_info(r, &s->oid, &s->size);
static void prep_temp_blob(struct index_state *istate,
			   const char *path, struct diff_tempfile *temp,
	if (convert_to_working_tree(istate, path,
static struct diff_tempfile *prepare_temp_file(struct repository *r,
					       const char *name,
					       struct diff_filespec *one)
	     reuse_worktree_file(r->index, name, &one->oid, 1))) {
			prep_temp_blob(r->index, name, temp, sb.buf, sb.len,
		if (diff_populate_filespec(r, one, 0))
		prep_temp_blob(r->index, name, temp,
			       one->data, one->size,
static void add_external_diff_name(struct repository *r,
				   struct argv_array *argv,
	struct diff_tempfile *temp = prepare_temp_file(r, name, df);
		add_external_diff_name(o->repo, &argv, name, one);
			add_external_diff_name(o->repo, &argv, name, two);
			add_external_diff_name(o->repo, &argv, other, two);
	diff_free_filespec_data(one);
	diff_free_filespec_data(two);
	if (one && two && !oideq(&one->oid, &two->oid)) {
			if ((!fill_mmfile(o->repo, &mf, one) &&
			     diff_filespec_is_binary(o->repo, one)) ||
			    (!fill_mmfile(o->repo, &mf, two) &&
			     diff_filespec_is_binary(o->repo, two)))
		struct userdiff_driver *drv;

		drv = userdiff_find_by_path(o->repo->index, attr_path);
		run_external_diff(pgm, name, other, one, two, xfrm_msg, o);
static void diff_fill_oid_info(struct diff_filespec *one, struct index_state *istate)
			if (index_path(istate, &one->oid, one->path, &st, 0))
	diff_fill_oid_info(one, o->repo->index);
	diff_fill_oid_info(two, o->repo->index);
			     one, null, &msg,
			     o, p);
		builtin_diffstat(p->one->path, NULL, NULL, NULL,
				 diffstat, o, p);
	diff_fill_oid_info(p->one, o->repo->index);
	diff_fill_oid_info(p->two, o->repo->index);
	builtin_diffstat(name, other, p->one, p->two,
			 diffstat, o, p);
	diff_fill_oid_info(p->one, o->repo->index);
	diff_fill_oid_info(p->two, o->repo->index);
static void prep_parse_options(struct diff_options *options);

void repo_diff_setup(struct repository *r, struct diff_options *options)
	options->repo = r;
	options->output_indicators[OUTPUT_INDICATOR_NEW] = '+';
	options->output_indicators[OUTPUT_INDICATOR_OLD] = '-';
	options->output_indicators[OUTPUT_INDICATOR_CONTEXT] = ' ';

	prep_parse_options(options);
	FREE_AND_NULL(options->parseopts);
static int diff_opt_stat(const struct option *opt, const char *value, int unset)
	struct diff_options *options = opt->value;
	char *end;
	BUG_ON_OPT_NEG(unset);
	if (!strcmp(opt->long_name, "stat")) {
		if (value) {
			width = strtoul(value, &end, 10);
			if (*end == ',')
				name_width = strtoul(end+1, &end, 10);
			if (*end == ',')
				count = strtoul(end+1, &end, 10);
			if (*end)
				return error(_("invalid --stat value: %s"), value);
	} else if (!strcmp(opt->long_name, "stat-width")) {
		width = strtoul(value, &end, 10);
		if (*end)
			return error(_("%s expects a numerical value"),
				     opt->long_name);
	} else if (!strcmp(opt->long_name, "stat-name-width")) {
		name_width = strtoul(value, &end, 10);
		if (*end)
			return error(_("%s expects a numerical value"),
				     opt->long_name);
	} else if (!strcmp(opt->long_name, "stat-graph-width")) {
		graph_width = strtoul(value, &end, 10);
		if (*end)
			return error(_("%s expects a numerical value"),
				     opt->long_name);
	} else if (!strcmp(opt->long_name, "stat-count")) {
		count = strtoul(value, &end, 10);
		if (*end)
			return error(_("%s expects a numerical value"),
				     opt->long_name);
	} else
		BUG("%s should not get here", opt->long_name);
	return 0;
unsigned diff_filter_bit(char status)
{
	prepare_filter_bits();
	return filter_bit[(int) status];
}

static int diff_opt_diff_filter(const struct option *option,
				const char *optarg, int unset)
	struct diff_options *opt = option->value;
	BUG_ON_OPT_NEG(unset);
			return error(_("unknown change class '%c' in --diff-filter=%s"),
				     optarg[i], optarg);
static void enable_patch_output(int *fmt)
{
static int diff_opt_ws_error_highlight(const struct option *option,
				       const char *arg, int unset)
	struct diff_options *opt = option->value;
	BUG_ON_OPT_NEG(unset);
	if (val < 0)
		return error(_("unknown value after ws-error-highlight=%.*s"),
			     -1 - val, arg);
	return 0;
static int diff_opt_find_object(const struct option *option,
				const char *arg, int unset)
	struct diff_options *opt = option->value;
	BUG_ON_OPT_NEG(unset);
		return error(_("unable to resolve '%s'"), arg);
	return 0;
static int diff_opt_anchored(const struct option *opt,
			     const char *arg, int unset)
	struct diff_options *options = opt->value;
	BUG_ON_OPT_NEG(unset);
	options->xdl_opts = DIFF_WITH_ALG(options, PATIENCE_DIFF);
	ALLOC_GROW(options->anchors, options->anchors_nr + 1,
		   options->anchors_alloc);
	options->anchors[options->anchors_nr++] = xstrdup(arg);
	return 0;
}
static int diff_opt_binary(const struct option *opt,
			   const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	BUG_ON_OPT_ARG(arg);
	enable_patch_output(&options->output_format);
	options->flags.binary = 1;
	return 0;
}

static int diff_opt_break_rewrites(const struct option *opt,
				   const char *arg, int unset)
{
	int *break_opt = opt->value;
	int opt1, opt2;

	BUG_ON_OPT_NEG(unset);
	if (!arg)
		arg = "";
	opt1 = parse_rename_score(&arg);
	if (*arg == 0)
		opt2 = 0;
	else if (*arg != '/')
		return error(_("%s expects <n>/<m> form"), opt->long_name);
	else {
		arg++;
		opt2 = parse_rename_score(&arg);
	if (*arg != 0)
		return error(_("%s expects <n>/<m> form"), opt->long_name);
	*break_opt = opt1 | (opt2 << 16);
	return 0;
}

static int diff_opt_char(const struct option *opt,
			 const char *arg, int unset)
{
	char *value = opt->value;

	BUG_ON_OPT_NEG(unset);
	if (arg[1])
		return error(_("%s expects a character, got '%s'"),
			     opt->long_name, arg);
	*value = arg[0];
	return 0;
}

static int diff_opt_color_moved(const struct option *opt,
				const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	if (unset) {
		options->color_moved = COLOR_MOVED_NO;
	} else if (!arg) {
	} else {
			return error(_("bad --color-moved argument: %s"), arg);
	return 0;
}

static int diff_opt_color_moved_ws(const struct option *opt,
				   const char *arg, int unset)
{
	struct diff_options *options = opt->value;
	unsigned cm;

	if (unset) {
		options->color_moved_ws_handling = 0;
		return 0;
	}

	cm = parse_color_moved_ws(arg);
	if (cm & COLOR_MOVED_WS_ERROR)
		return error(_("invalid mode '%s' in --color-moved-ws"), arg);
	options->color_moved_ws_handling = cm;
	return 0;
}

static int diff_opt_color_words(const struct option *opt,
				const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	options->use_color = 1;
	options->word_diff = DIFF_WORDS_COLOR;
	options->word_regex = arg;
	return 0;
}

static int diff_opt_compact_summary(const struct option *opt,
				    const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_ARG(arg);
	if (unset) {
		options->flags.stat_with_summary = 0;
	} else {
		options->flags.stat_with_summary = 1;
		options->output_format |= DIFF_FORMAT_DIFFSTAT;
	}
	return 0;
}

static int diff_opt_diff_algorithm(const struct option *opt,
				   const char *arg, int unset)
{
	struct diff_options *options = opt->value;
	long value = parse_algorithm_value(arg);

	BUG_ON_OPT_NEG(unset);
	if (value < 0)
		return error(_("option diff-algorithm accepts \"myers\", "
			       "\"minimal\", \"patience\" and \"histogram\""));

	/* clear out previous settings */
	DIFF_XDL_CLR(options, NEED_MINIMAL);
	options->xdl_opts &= ~XDF_DIFF_ALGORITHM_MASK;
	options->xdl_opts |= value;
	return 0;
}

static int diff_opt_dirstat(const struct option *opt,
			    const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	if (!strcmp(opt->long_name, "cumulative")) {
		if (arg)
			BUG("how come --cumulative take a value?");
		arg = "cumulative";
	} else if (!strcmp(opt->long_name, "dirstat-by-file"))
		parse_dirstat_opt(options, "files");
	parse_dirstat_opt(options, arg ? arg : "");
	return 0;
}

static int diff_opt_find_copies(const struct option *opt,
				const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	if (!arg)
		arg = "";
	options->rename_score = parse_rename_score(&arg);
	if (*arg != 0)
		return error(_("invalid argument to %s"), opt->long_name);

	if (options->detect_rename == DIFF_DETECT_COPY)
		options->flags.find_copies_harder = 1;
	else
		options->detect_rename = DIFF_DETECT_COPY;

	return 0;
}

static int diff_opt_find_renames(const struct option *opt,
				 const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	if (!arg)
		arg = "";
	options->rename_score = parse_rename_score(&arg);
	if (*arg != 0)
		return error(_("invalid argument to %s"), opt->long_name);

	options->detect_rename = DIFF_DETECT_RENAME;
	return 0;
}

static int diff_opt_follow(const struct option *opt,
			   const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_ARG(arg);
	if (unset) {
		options->flags.follow_renames = 0;
		options->flags.default_follow_renames = 0;
	} else {
		options->flags.follow_renames = 1;
	return 0;
}

static int diff_opt_ignore_submodules(const struct option *opt,
				      const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	if (!arg)
		arg = "all";
	options->flags.override_submodule_config = 1;
	handle_ignore_submodules_arg(options, arg);
	return 0;
}

static int diff_opt_line_prefix(const struct option *opt,
				const char *optarg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	options->line_prefix = optarg;
	options->line_prefix_length = strlen(options->line_prefix);
	graph_setup_line_prefix(options);
	return 0;
}

static int diff_opt_no_prefix(const struct option *opt,
			      const char *optarg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	BUG_ON_OPT_ARG(optarg);
	options->a_prefix = "";
	options->b_prefix = "";
	return 0;
}

static enum parse_opt_result diff_opt_output(struct parse_opt_ctx_t *ctx,
					     const struct option *opt,
					     const char *arg, int unset)
{
	struct diff_options *options = opt->value;
	char *path;

	BUG_ON_OPT_NEG(unset);
	path = prefix_filename(ctx->prefix, arg);
	options->file = xfopen(path, "w");
	options->close_file = 1;
	if (options->use_color != GIT_COLOR_ALWAYS)
		options->use_color = GIT_COLOR_NEVER;
	free(path);
	return 0;
}

static int diff_opt_patience(const struct option *opt,
			     const char *arg, int unset)
{
	struct diff_options *options = opt->value;
	int i;

	BUG_ON_OPT_NEG(unset);
	BUG_ON_OPT_ARG(arg);
	options->xdl_opts = DIFF_WITH_ALG(options, PATIENCE_DIFF);
	/*
	 * Both --patience and --anchored use PATIENCE_DIFF
	 * internally, so remove any anchors previously
	 * specified.
	 */
	for (i = 0; i < options->anchors_nr; i++)
		free(options->anchors[i]);
	options->anchors_nr = 0;
	return 0;
}

static int diff_opt_pickaxe_regex(const struct option *opt,
				  const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	options->pickaxe = arg;
	options->pickaxe_opts |= DIFF_PICKAXE_KIND_G;
	return 0;
}

static int diff_opt_pickaxe_string(const struct option *opt,
				   const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	options->pickaxe = arg;
	options->pickaxe_opts |= DIFF_PICKAXE_KIND_S;
	return 0;
}

static int diff_opt_relative(const struct option *opt,
			     const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	options->flags.relative_name = 1;
	if (arg)
		options->prefix = arg;
	return 0;
}

static int diff_opt_submodule(const struct option *opt,
			      const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	if (!arg)
		arg = "log";
	if (parse_submodule_params(options, arg))
		return error(_("failed to parse --submodule option parameter: '%s'"),
			     arg);
	return 0;
}

static int diff_opt_textconv(const struct option *opt,
			     const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_ARG(arg);
	if (unset) {
		options->flags.allow_textconv = 0;
	} else {
		options->flags.allow_textconv = 1;
		options->flags.textconv_set_via_cmdline = 1;
	}
	return 0;
}

static int diff_opt_unified(const struct option *opt,
			    const char *arg, int unset)
{
	struct diff_options *options = opt->value;
	char *s;

	BUG_ON_OPT_NEG(unset);

	if (arg) {
		options->context = strtol(arg, &s, 10);
		if (*s)
			return error(_("%s expects a numerical value"), "--unified");
	}
	enable_patch_output(&options->output_format);

	return 0;
}

static int diff_opt_word_diff(const struct option *opt,
			      const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	if (arg) {
			return error(_("bad --word-diff argument: %s"), arg);
	} else {
	return 0;
}

static int diff_opt_word_diff_regex(const struct option *opt,
				    const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	if (options->word_diff == DIFF_WORDS_NONE)
		options->word_diff = DIFF_WORDS_PLAIN;
	options->word_regex = arg;
	return 0;
}

static void prep_parse_options(struct diff_options *options)
{
	struct option parseopts[] = {
		OPT_GROUP(N_("Diff output format options")),
		OPT_BITOP('p', "patch", &options->output_format,
			  N_("generate patch"),
			  DIFF_FORMAT_PATCH, DIFF_FORMAT_NO_OUTPUT),
		OPT_BIT_F('s', "no-patch", &options->output_format,
			  N_("suppress diff output"),
			  DIFF_FORMAT_NO_OUTPUT, PARSE_OPT_NONEG),
		OPT_BITOP('u', NULL, &options->output_format,
			  N_("generate patch"),
			  DIFF_FORMAT_PATCH, DIFF_FORMAT_NO_OUTPUT),
		OPT_CALLBACK_F('U', "unified", options, N_("<n>"),
			       N_("generate diffs with <n> lines context"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG, diff_opt_unified),
		OPT_BOOL('W', "function-context", &options->flags.funccontext,
			 N_("generate diffs with <n> lines context")),
		OPT_BIT_F(0, "raw", &options->output_format,
			  N_("generate the diff in raw format"),
			  DIFF_FORMAT_RAW, PARSE_OPT_NONEG),
		OPT_BITOP(0, "patch-with-raw", &options->output_format,
			  N_("synonym for '-p --raw'"),
			  DIFF_FORMAT_PATCH | DIFF_FORMAT_RAW,
			  DIFF_FORMAT_NO_OUTPUT),
		OPT_BITOP(0, "patch-with-stat", &options->output_format,
			  N_("synonym for '-p --stat'"),
			  DIFF_FORMAT_PATCH | DIFF_FORMAT_DIFFSTAT,
			  DIFF_FORMAT_NO_OUTPUT),
		OPT_BIT_F(0, "numstat", &options->output_format,
			  N_("machine friendly --stat"),
			  DIFF_FORMAT_NUMSTAT, PARSE_OPT_NONEG),
		OPT_BIT_F(0, "shortstat", &options->output_format,
			  N_("output only the last line of --stat"),
			  DIFF_FORMAT_SHORTSTAT, PARSE_OPT_NONEG),
		OPT_CALLBACK_F('X', "dirstat", options, N_("<param1,param2>..."),
			       N_("output the distribution of relative amount of changes for each sub-directory"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG,
			       diff_opt_dirstat),
		OPT_CALLBACK_F(0, "cumulative", options, NULL,
			       N_("synonym for --dirstat=cumulative"),
			       PARSE_OPT_NONEG | PARSE_OPT_NOARG,
			       diff_opt_dirstat),
		OPT_CALLBACK_F(0, "dirstat-by-file", options, N_("<param1,param2>..."),
			       N_("synonym for --dirstat=files,param1,param2..."),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG,
			       diff_opt_dirstat),
		OPT_BIT_F(0, "check", &options->output_format,
			  N_("warn if changes introduce conflict markers or whitespace errors"),
			  DIFF_FORMAT_CHECKDIFF, PARSE_OPT_NONEG),
		OPT_BIT_F(0, "summary", &options->output_format,
			  N_("condensed summary such as creations, renames and mode changes"),
			  DIFF_FORMAT_SUMMARY, PARSE_OPT_NONEG),
		OPT_BIT_F(0, "name-only", &options->output_format,
			  N_("show only names of changed files"),
			  DIFF_FORMAT_NAME, PARSE_OPT_NONEG),
		OPT_BIT_F(0, "name-status", &options->output_format,
			  N_("show only names and status of changed files"),
			  DIFF_FORMAT_NAME_STATUS, PARSE_OPT_NONEG),
		OPT_CALLBACK_F(0, "stat", options, N_("<width>[,<name-width>[,<count>]]"),
			       N_("generate diffstat"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG, diff_opt_stat),
		OPT_CALLBACK_F(0, "stat-width", options, N_("<width>"),
			       N_("generate diffstat with a given width"),
			       PARSE_OPT_NONEG, diff_opt_stat),
		OPT_CALLBACK_F(0, "stat-name-width", options, N_("<width>"),
			       N_("generate diffstat with a given name width"),
			       PARSE_OPT_NONEG, diff_opt_stat),
		OPT_CALLBACK_F(0, "stat-graph-width", options, N_("<width>"),
			       N_("generate diffstat with a given graph width"),
			       PARSE_OPT_NONEG, diff_opt_stat),
		OPT_CALLBACK_F(0, "stat-count", options, N_("<count>"),
			       N_("generate diffstat with limited lines"),
			       PARSE_OPT_NONEG, diff_opt_stat),
		OPT_CALLBACK_F(0, "compact-summary", options, NULL,
			       N_("generate compact summary in diffstat"),
			       PARSE_OPT_NOARG, diff_opt_compact_summary),
		OPT_CALLBACK_F(0, "binary", options, NULL,
			       N_("output a binary diff that can be applied"),
			       PARSE_OPT_NONEG | PARSE_OPT_NOARG, diff_opt_binary),
		OPT_BOOL(0, "full-index", &options->flags.full_index,
			 N_("show full pre- and post-image object names on the \"index\" lines")),
		OPT_COLOR_FLAG(0, "color", &options->use_color,
			       N_("show colored diff")),
		OPT_CALLBACK_F(0, "ws-error-highlight", options, N_("<kind>"),
			       N_("highlight whitespace errors in the 'context', 'old' or 'new' lines in the diff"),
			       PARSE_OPT_NONEG, diff_opt_ws_error_highlight),
		OPT_SET_INT('z', NULL, &options->line_termination,
			    N_("do not munge pathnames and use NULs as output field terminators in --raw or --numstat"),
			    0),
		OPT__ABBREV(&options->abbrev),
		OPT_STRING_F(0, "src-prefix", &options->a_prefix, N_("<prefix>"),
			     N_("show the given source prefix instead of \"a/\""),
			     PARSE_OPT_NONEG),
		OPT_STRING_F(0, "dst-prefix", &options->b_prefix, N_("<prefix>"),
			     N_("show the given destination prefix instead of \"b/\""),
			     PARSE_OPT_NONEG),
		OPT_CALLBACK_F(0, "line-prefix", options, N_("<prefix>"),
			       N_("prepend an additional prefix to every line of output"),
			       PARSE_OPT_NONEG, diff_opt_line_prefix),
		OPT_CALLBACK_F(0, "no-prefix", options, NULL,
			       N_("do not show any source or destination prefix"),
			       PARSE_OPT_NONEG | PARSE_OPT_NOARG, diff_opt_no_prefix),
		OPT_INTEGER_F(0, "inter-hunk-context", &options->interhunkcontext,
			      N_("show context between diff hunks up to the specified number of lines"),
			      PARSE_OPT_NONEG),
		OPT_CALLBACK_F(0, "output-indicator-new",
			       &options->output_indicators[OUTPUT_INDICATOR_NEW],
			       N_("<char>"),
			       N_("specify the character to indicate a new line instead of '+'"),
			       PARSE_OPT_NONEG, diff_opt_char),
		OPT_CALLBACK_F(0, "output-indicator-old",
			       &options->output_indicators[OUTPUT_INDICATOR_OLD],
			       N_("<char>"),
			       N_("specify the character to indicate an old line instead of '-'"),
			       PARSE_OPT_NONEG, diff_opt_char),
		OPT_CALLBACK_F(0, "output-indicator-context",
			       &options->output_indicators[OUTPUT_INDICATOR_CONTEXT],
			       N_("<char>"),
			       N_("specify the character to indicate a context instead of ' '"),
			       PARSE_OPT_NONEG, diff_opt_char),

		OPT_GROUP(N_("Diff rename options")),
		OPT_CALLBACK_F('B', "break-rewrites", &options->break_opt, N_("<n>[/<m>]"),
			       N_("break complete rewrite changes into pairs of delete and create"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG,
			       diff_opt_break_rewrites),
		OPT_CALLBACK_F('M', "find-renames", options, N_("<n>"),
			       N_("detect renames"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG,
			       diff_opt_find_renames),
		OPT_SET_INT_F('D', "irreversible-delete", &options->irreversible_delete,
			      N_("omit the preimage for deletes"),
			      1, PARSE_OPT_NONEG),
		OPT_CALLBACK_F('C', "find-copies", options, N_("<n>"),
			       N_("detect copies"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG,
			       diff_opt_find_copies),
		OPT_BOOL(0, "find-copies-harder", &options->flags.find_copies_harder,
			 N_("use unmodified files as source to find copies")),
		OPT_SET_INT_F(0, "no-renames", &options->detect_rename,
			      N_("disable rename detection"),
			      0, PARSE_OPT_NONEG),
		OPT_BOOL(0, "rename-empty", &options->flags.rename_empty,
			 N_("use empty blobs as rename source")),
		OPT_CALLBACK_F(0, "follow", options, NULL,
			       N_("continue listing the history of a file beyond renames"),
			       PARSE_OPT_NOARG, diff_opt_follow),
		OPT_INTEGER('l', NULL, &options->rename_limit,
			    N_("prevent rename/copy detection if the number of rename/copy targets exceeds given limit")),

		OPT_GROUP(N_("Diff algorithm options")),
		OPT_BIT(0, "minimal", &options->xdl_opts,
			N_("produce the smallest possible diff"),
			XDF_NEED_MINIMAL),
		OPT_BIT_F('w', "ignore-all-space", &options->xdl_opts,
			  N_("ignore whitespace when comparing lines"),
			  XDF_IGNORE_WHITESPACE, PARSE_OPT_NONEG),
		OPT_BIT_F('b', "ignore-space-change", &options->xdl_opts,
			  N_("ignore changes in amount of whitespace"),
			  XDF_IGNORE_WHITESPACE_CHANGE, PARSE_OPT_NONEG),
		OPT_BIT_F(0, "ignore-space-at-eol", &options->xdl_opts,
			  N_("ignore changes in whitespace at EOL"),
			  XDF_IGNORE_WHITESPACE_AT_EOL, PARSE_OPT_NONEG),
		OPT_BIT_F(0, "ignore-cr-at-eol", &options->xdl_opts,
			  N_("ignore carrier-return at the end of line"),
			  XDF_IGNORE_CR_AT_EOL, PARSE_OPT_NONEG),
		OPT_BIT_F(0, "ignore-blank-lines", &options->xdl_opts,
			  N_("ignore changes whose lines are all blank"),
			  XDF_IGNORE_BLANK_LINES, PARSE_OPT_NONEG),
		OPT_BIT(0, "indent-heuristic", &options->xdl_opts,
			N_("heuristic to shift diff hunk boundaries for easy reading"),
			XDF_INDENT_HEURISTIC),
		OPT_CALLBACK_F(0, "patience", options, NULL,
			       N_("generate diff using the \"patience diff\" algorithm"),
			       PARSE_OPT_NONEG | PARSE_OPT_NOARG,
			       diff_opt_patience),
		OPT_BITOP(0, "histogram", &options->xdl_opts,
			  N_("generate diff using the \"histogram diff\" algorithm"),
			  XDF_HISTOGRAM_DIFF, XDF_DIFF_ALGORITHM_MASK),
		OPT_CALLBACK_F(0, "diff-algorithm", options, N_("<algorithm>"),
			       N_("choose a diff algorithm"),
			       PARSE_OPT_NONEG, diff_opt_diff_algorithm),
		OPT_CALLBACK_F(0, "anchored", options, N_("<text>"),
			       N_("generate diff using the \"anchored diff\" algorithm"),
			       PARSE_OPT_NONEG, diff_opt_anchored),
		OPT_CALLBACK_F(0, "word-diff", options, N_("<mode>"),
			       N_("show word diff, using <mode> to delimit changed words"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG, diff_opt_word_diff),
		OPT_CALLBACK_F(0, "word-diff-regex", options, N_("<regex>"),
			       N_("use <regex> to decide what a word is"),
			       PARSE_OPT_NONEG, diff_opt_word_diff_regex),
		OPT_CALLBACK_F(0, "color-words", options, N_("<regex>"),
			       N_("equivalent to --word-diff=color --word-diff-regex=<regex>"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG, diff_opt_color_words),
		OPT_CALLBACK_F(0, "color-moved", options, N_("<mode>"),
			       N_("moved lines of code are colored differently"),
			       PARSE_OPT_OPTARG, diff_opt_color_moved),
		OPT_CALLBACK_F(0, "color-moved-ws", options, N_("<mode>"),
			       N_("how white spaces are ignored in --color-moved"),
			       0, diff_opt_color_moved_ws),

		OPT_GROUP(N_("Other diff options")),
		OPT_CALLBACK_F(0, "relative", options, N_("<prefix>"),
			       N_("when run from subdir, exclude changes outside and show relative paths"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG,
			       diff_opt_relative),
		OPT_BOOL('a', "text", &options->flags.text,
			 N_("treat all files as text")),
		OPT_BOOL('R', NULL, &options->flags.reverse_diff,
			 N_("swap two inputs, reverse the diff")),
		OPT_BOOL(0, "exit-code", &options->flags.exit_with_status,
			 N_("exit with 1 if there were differences, 0 otherwise")),
		OPT_BOOL(0, "quiet", &options->flags.quick,
			 N_("disable all output of the program")),
		OPT_BOOL(0, "ext-diff", &options->flags.allow_external,
			 N_("allow an external diff helper to be executed")),
		OPT_CALLBACK_F(0, "textconv", options, NULL,
			       N_("run external text conversion filters when comparing binary files"),
			       PARSE_OPT_NOARG, diff_opt_textconv),
		OPT_CALLBACK_F(0, "ignore-submodules", options, N_("<when>"),
			       N_("ignore changes to submodules in the diff generation"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG,
			       diff_opt_ignore_submodules),
		OPT_CALLBACK_F(0, "submodule", options, N_("<format>"),
			       N_("specify how differences in submodules are shown"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG,
			       diff_opt_submodule),
		OPT_SET_INT_F(0, "ita-invisible-in-index", &options->ita_invisible_in_index,
			      N_("hide 'git add -N' entries from the index"),
			      1, PARSE_OPT_NONEG),
		OPT_SET_INT_F(0, "ita-visible-in-index", &options->ita_invisible_in_index,
			      N_("treat 'git add -N' entries as real in the index"),
			      0, PARSE_OPT_NONEG),
		OPT_CALLBACK_F('S', NULL, options, N_("<string>"),
			       N_("look for differences that change the number of occurrences of the specified string"),
			       0, diff_opt_pickaxe_string),
		OPT_CALLBACK_F('G', NULL, options, N_("<regex>"),
			       N_("look for differences that change the number of occurrences of the specified regex"),
			       0, diff_opt_pickaxe_regex),
		OPT_BIT_F(0, "pickaxe-all", &options->pickaxe_opts,
			  N_("show all changes in the changeset with -S or -G"),
			  DIFF_PICKAXE_ALL, PARSE_OPT_NONEG),
		OPT_BIT_F(0, "pickaxe-regex", &options->pickaxe_opts,
			  N_("treat <string> in -S as extended POSIX regular expression"),
			  DIFF_PICKAXE_REGEX, PARSE_OPT_NONEG),
		OPT_FILENAME('O', NULL, &options->orderfile,
			     N_("control the order in which files appear in the output")),
		OPT_CALLBACK_F(0, "find-object", options, N_("<object-id>"),
			       N_("look for differences that change the number of occurrences of the specified object"),
			       PARSE_OPT_NONEG, diff_opt_find_object),
		OPT_CALLBACK_F(0, "diff-filter", options, N_("[(A|C|D|M|R|T|U|X|B)...[*]]"),
			       N_("select files by diff type"),
			       PARSE_OPT_NONEG, diff_opt_diff_filter),
		{ OPTION_CALLBACK, 0, "output", options, N_("<file>"),
		  N_("Output to a specific file"),
		  PARSE_OPT_NONEG, NULL, 0, diff_opt_output },

		OPT_END()
	};

	ALLOC_ARRAY(options->parseopts, ARRAY_SIZE(parseopts));
	memcpy(options->parseopts, parseopts, sizeof(parseopts));
}

int diff_opt_parse(struct diff_options *options,
		   const char **av, int ac, const char *prefix)
{
	if (!prefix)
		prefix = "";

	ac = parse_options(ac, av, prefix, options->parseopts, NULL,
			   PARSE_OPT_KEEP_DASHDASH |
			   PARSE_OPT_KEEP_UNKNOWN |
			   PARSE_OPT_NO_INTERNAL_HELP |
			   PARSE_OPT_ONE_SHOT |
			   PARSE_OPT_STOP_AT_NON_OPTION);

	return ac;
	    oideq(&one->oid, &two->oid) &&
		else if (!oideq(&p->one->oid, &p->two->oid) ||
	git_hash_ctx *ctx;
void flush_one_hunk(struct object_id *result, git_hash_ctx *ctx)
{
	unsigned char hash[GIT_MAX_RAWSZ];
	unsigned short carry = 0;
	int i;

	the_hash_algo->final_fn(hash, ctx);
	the_hash_algo->init_fn(ctx);
	/* 20-byte sum, with carry */
	for (i = 0; i < the_hash_algo->rawsz; ++i) {
		carry += result->hash[i] + hash[i];
		result->hash[i] = carry;
		carry >>= 8;
	}
}

	the_hash_algo->update_fn(data->ctx, line, new_len);
static void patch_id_add_string(git_hash_ctx *ctx, const char *str)
	the_hash_algo->update_fn(ctx, str, strlen(str));
static void patch_id_add_mode(git_hash_ctx *ctx, unsigned mode)
	the_hash_algo->update_fn(ctx, buf, len);
/* returns 0 upon success, and writes result into oid */
static int diff_get_patch_id(struct diff_options *options, struct object_id *oid, int diff_header_only, int stable)
	git_hash_ctx ctx;
	the_hash_algo->init_fn(&ctx);
	oidclr(oid);
		diff_fill_oid_info(p->one, options->repo->index);
		diff_fill_oid_info(p->two, options->repo->index);
		the_hash_algo->update_fn(&ctx, p->one->path, len1);
		the_hash_algo->update_fn(&ctx, p->two->path, len2);
			the_hash_algo->update_fn(&ctx, p->two->path, len2);
			the_hash_algo->update_fn(&ctx, p->one->path, len1);
			the_hash_algo->update_fn(&ctx, p->one->path, len1);
			the_hash_algo->update_fn(&ctx, p->two->path, len2);
		if (fill_mmfile(options->repo, &mf1, p->one) < 0 ||
		    fill_mmfile(options->repo, &mf2, p->two) < 0)
		if (diff_filespec_is_binary(options->repo, p->one) ||
		    diff_filespec_is_binary(options->repo, p->two)) {
			the_hash_algo->update_fn(&ctx, oid_to_hex(&p->one->oid),
					the_hash_algo->hexsz);
			the_hash_algo->update_fn(&ctx, oid_to_hex(&p->two->oid),
					the_hash_algo->hexsz);
		if (xdi_diff_outf(&mf1, &mf2, discard_hunk_line,
				  patch_id_consume, &data, &xpp, &xecfg))

		if (stable)
			flush_one_hunk(oid, &ctx);
	if (!stable)
		the_hash_algo->final_fn(oid->hash, &ctx);

int diff_flush_patch_id(struct diff_options *options, struct object_id *oid, int diff_header_only, int stable)
	int result = diff_get_patch_id(options, oid, diff_header_only, stable);
			hashmap_free_entries(&add_lines, struct moved_entry,
						ent);
			hashmap_free_entries(&del_lines, struct moved_entry,
						ent);
		esm.nr = 0;

		o->emitted_symbols = NULL;
		compute_diffstat(options, &diffstat, q);
static int diff_filespec_is_identical(struct repository *r,
				      struct diff_filespec *one,
	if (diff_populate_filespec(r, one, 0))
	if (diff_populate_filespec(r, two, 0))
static int diff_filespec_check_stat_unmatch(struct repository *r,
					    struct diff_filepair *p)
	    diff_populate_filespec(r, p->one, CHECK_SIZE_ONLY) ||
	    diff_populate_filespec(r, p->two, CHECK_SIZE_ONLY) ||
	    !diff_filespec_is_identical(r, p->one, p->two)) /* (2) */
		if (diff_filespec_check_stat_unmatch(diffopt->repo, p))
void diffcore_fix_diff_index(void)
static void add_if_missing(struct repository *r,
			   struct oid_array *to_fetch,
			   const struct diff_filespec *filespec)
{
	if (filespec && filespec->oid_valid &&
	    !S_ISGITLINK(filespec->mode) &&
	    oid_object_info_extended(r, &filespec->oid, NULL,
				     OBJECT_INFO_FOR_PREFETCH))
		oid_array_append(to_fetch, &filespec->oid);
}

	if (options->repo == the_repository && has_promisor_remote()) {
		/*
		 * Prefetch the diff pairs that are about to be flushed.
		 */
		int i;
		struct diff_queue_struct *q = &diff_queued_diff;
		struct oid_array to_fetch = OID_ARRAY_INIT;

		for (i = 0; i < q->nr; i++) {
			struct diff_filepair *p = q->queue[i];
			add_if_missing(options->repo, &to_fetch, p->one);
			add_if_missing(options->repo, &to_fetch, p->two);
		}
		if (to_fetch.nr)
			/*
			 * NEEDSWORK: Consider deduplicating the OIDs sent.
			 */
			promisor_remote_get_direct(options->repo,
						   to_fetch.oid, to_fetch.nr);
		oid_array_clear(&to_fetch);
	}

			diffcore_break(options->repo,
				       options->break_opt);
void compute_diffstat(struct diff_options *options,
		      struct diffstat_t *diffstat,
		      struct diff_queue_struct *q)
{
	int i;

	memset(diffstat, 0, sizeof(struct diffstat_t));
	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];
		if (check_pair_status(p))
			diff_flush_stat(p, options, diffstat);
	}
}

	    !diff_filespec_check_stat_unmatch(options->repo, p))
static char *run_textconv(struct repository *r,
			  const char *pgm,
			  struct diff_filespec *spec,
			  size_t *outsize)
	temp = prepare_temp_file(r, spec->path, spec);
size_t fill_textconv(struct repository *r,
		     struct userdiff_driver *driver,
		if (diff_populate_filespec(r, df, 0))
	*outbuf = run_textconv(r, driver->textconv, df, &size);
int textconv_object(struct repository *r,
		    const char *path,
	textconv = get_textconv(r, df);
	*buf_size = fill_textconv(r, textconv, df, buf);